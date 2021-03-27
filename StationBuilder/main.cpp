#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include "isometricLevel.h"
#include "textureManager.h"
#include "gameManager.h"
#include "station.h"
#include "fps.h"
#include <iostream>
#include <fstream>


const float zoomAmount{ 1.1f };
sf::Vector2f oldPos;
bool moving = false;
void zoomViewAt(sf::Vector2i pixel, sf::RenderWindow& window, float zoom)
{
    const sf::Vector2f beforeCoord{ window.mapPixelToCoords(pixel) };
    sf::View view{ window.getView() };
    view.zoom(zoom);
    window.setView(view);
    const sf::Vector2f afterCoord{ window.mapPixelToCoords(pixel) };
    const sf::Vector2f offsetCoords{ beforeCoord - afterCoord };
    view.move(offsetCoords);
    window.setView(view);
}


int main()
{
    int screenWidth = 1280;
    int screenHeight = 720;

    
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "SFML works!", sf::Style::Default, settings);
    sf::Clock clock;
    FPS fps;
    tgui::Gui gui{ window };
    gui.loadWidgetsFromFile("stationGUI.txt");
    tgui::BitmapButton::Ptr upLayerBut = gui.get<tgui::BitmapButton>("upLayer");
    tgui::BitmapButton::Ptr downLayerBut = gui.get<tgui::BitmapButton>("downLayer");
    tgui::Label::Ptr currentLayerLabel = gui.get<tgui::Label>("currentLayer");
   
    gameManager gameMaster;
    //this is master global scope object to hold al our textures for all levels,
    //we must pass a pointer of this to all isometricLevels so they can get their textures.
    //add new textures using addTexture("name", "filename"), get them by using getTexture("name")
    //returns a pointer to the texture, this keeps them always in scope for any sprite of any level
    textureManager textureMaster;
    textureMaster.addTexture("empty", "empty64white.png");
    textureMaster.addTexture("floor", "floor64.png");
    station HaxelPort(&textureMaster);
    HaxelPort.appendNewIsoLevel(40, 40, 64);
    HaxelPort.appendNewIsoLevel(40, 40, 64, "floor");

    //isometricLevel layerOne(&textureMaster,40,40,64);
    isometricLevel layerTwo;
    //layerOne.fillFloors();
    //gameMaster.saveLevelToDisc(layerOne, "test2");
    gameMaster.loadLevelFromDisc(layerTwo, "test2", &textureMaster);
    HaxelPort.addIsoLevel(layerTwo, 2);
   
    upLayerBut->connect("pressed", &station::incCurrentLevel, &HaxelPort);
    downLayerBut->connect("pressed", &station::decCurrentLevel, &HaxelPort);
    
    
    sf::View view(window.getDefaultView());
    window.clear(sf::Color::White);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            gui.handleEvent(event);
            if (event.type == sf::Event::Closed)
            { 
                window.close();
            }
                // Pass the event to the widgets

            else if (event.type == sf::Event::MouseWheelScrolled)
            {

                if (event.mouseWheelScroll.delta > 0)
                    zoomViewAt({ event.mouseWheelScroll.x, event.mouseWheelScroll.y }, window, (1.f / zoomAmount));

                else if (event.mouseWheelScroll.delta < 0)
                    zoomViewAt({ event.mouseWheelScroll.x, event.mouseWheelScroll.y }, window, zoomAmount);
            }

            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == 1) {
                    moving = true;
                    oldPos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                }
            }
            else if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == 1) {
                    moving = false;
                }
            }
            else if (event.type == sf::Event::MouseMoved)
            {
                if (!moving)
                    break;
                // Determine the new position in world coordinates
                const sf::Vector2f newPos = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
                // Determine how the cursor has moved
                // Swap these to invert the movement direction
                const sf::Vector2f deltaPos = oldPos - newPos;
                // Move our view accordingly and update the window
                view.move(deltaPos);

                window.setView(view);
                //window.setView(window.getDefaultView());
                // Save the new position as the old one
                // We're recalculating this, since we've changed the view
                oldPos = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
            }
            else if (event.type == sf::Event::Resized)
            {
                sf::Vector2u size = window.getSize();
                unsigned int width = size.x;
                unsigned int height = size.y;

                view.setSize(size.x, size.y);
                window.setView(view);
                
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::PageUp)
                {
                    HaxelPort.incCurrentLevel();
                }
                else if (event.key.code == sf::Keyboard::PageDown)
                {
                    HaxelPort.decCurrentLevel();
                }
            }

        }

        window.clear(sf::Color::Black);
        currentLayerLabel->setText(std::to_string(HaxelPort.getCurrentLevel()));
        HaxelPort.drawLayer(window,HaxelPort.getCurrentLevel());
        gui.draw();//draw this last so it is always ontop. Should probably use a differnet view for it eventually.
        //layerOne.draw(window);
        window.display();
        fps.update();
        std::ostringstream ss;
        ss << "FPS: " << fps.getFPS();

        window.setTitle(ss.str());
    }

    return 0;
}
