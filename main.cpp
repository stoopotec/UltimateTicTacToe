#include <iostream>
#include <SFML/Graphics.hpp>

#include "playground.hpp"
#include "player.hpp"
#include "interface.hpp"

using namespace sf;

#define PHI 1.618033988749

Resources resources = Resources();


Player *player1, *player2;
playground g = playground();


void p1_move(pos_t pos) {
    printf("player1 moved at %i, %i\n", (int)(pos & 0b1111), (int)(pos >> 4));
}

void p2_move(pos_t pos) {
    printf("player2 moved at %i, %i\n", (int)(pos & 0b1111), (int)(pos >> 4));
}

void process_click(pos_t* poses, int poses_len, Grid& senders) {
    //printf("clicked at %i, %i, move is %i\n", (int)(pos & 0b1111), (int)(pos >> 4), g.move(pos) ? 1 : 0);
    printf("click\n");
}

int main(int argc, char** argv)
{
    ContextSettings settings = ContextSettings(0U, 0U, 3U, 1U, 1U, 0U, false);
    RenderWindow window(VideoMode(700 * PHI, 700), "UltimateTicTacToe", 7U, settings);
    Mouse mouse = Mouse();
    sf::Vector2u mousePos = sf::Vector2u(0.0f, 0.0f);

    Box body = Box((sf::Vector2f)window.getSize(), resources);

    
    Grid grid = Grid(process_click, 1, sf::Vector2f(600, 600), resources);
    body.Childs.push_back(&grid);

    

    GraphicPlayer gp1 = GraphicPlayer(p1_move);
    GraphicPlayer gp2 = GraphicPlayer(p2_move);


    CircleShape cursor = CircleShape(10);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::Resized) {
                window.setView(View(sf::FloatRect(Vector2f(0.0f, 0.0f), (Vector2f)window.getSize())));
            }
            if (event.type == Event::MouseMoved) {
                mousePos = (Vector2u)mouse.getPosition(window);
            }
            if (event.type == Event::MouseButtonPressed) {
                mousePos = (Vector2u)mouse.getPosition(window);
                body.processClick(mousePos);
            }
        }




        window.clear(resources.BackgroundColor);
        window.draw(body);
        
        cursor.setPosition((sf::Vector2f)mousePos - sf::Vector2f(cursor.getRadius(), cursor.getRadius()));
        window.draw(cursor);

        window.display();
    }


    return 0;
}