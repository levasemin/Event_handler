#pragma GCC diagnostic ignored "-Wunused-parameter"

#pragma once

#include "Color.h"
#include <SFML/Graphics.hpp>
#include "Sprite.h"
#include "Event.h"

class Window
{

public:
    sf::RenderWindow window_;
    
    Window(Vector2d shape, int style = 7):
        window_(sf::VideoMode((uint32_t)shape.x_, (uint32_t)shape.y_), "", style)
        {
        };
        
    void draw(const sf::Vertex *vertices, std::size_t VertexCount, sf::PrimitiveType type, const sf::RenderStates &states = sf::RenderStates::Default);
    void draw(const sf::Drawable &drawable,                                                const sf::RenderStates &states = sf::RenderStates::Default);
    void draw(const sf::VertexBuffer &vertexBuffer,                                        const sf::RenderStates &states = sf::RenderStates::Default);	
    void draw(Sprite sprite);
    void clear();
    
    Window (const Window &source):
        window_(sf::VideoMode(source.window_.getSize().x, source.window_.getSize().y), "Vectors")
    {}

    Window &operator =(const Window &source)
    {
        window_.create(sf::VideoMode(source.window_.getSize().x, source.window_.getSize().y), "Vectors");
        return *this;
    }    
    
    bool isOpen();
    bool pollEvent(Event &event);
    void close();
    void display();
    void clear(Color color);
};