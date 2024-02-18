#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

using namespace sf;
using namespace std;

class ShapeBuilder {
private:
    CircleShape shape;
public:
    ShapeBuilder(int size = 5.f) : shape(size) {}

    ShapeBuilder &setPoints(size_t points) {
        shape.setPointCount(points);
        return *this;
    }

    ShapeBuilder &setColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha = 255) {
        shape.setFillColor(Color(red, green, blue, alpha));
        return *this;
    }

    ShapeBuilder &setRotation(float angle) {
        shape.setRotation(angle);
        return *this;
    }

    ShapeBuilder &setPosition(float x, float y) {
        shape.setPosition(Vector2f(x, y));
        return *this;
    }

    ShapeBuilder &setSize(float size) {
        shape.setRadius(size);
        return *this;
    }

    ShapeBuilder &setOrigin(float x_offset, float y_offset) {
        shape.setOrigin(x_offset, y_offset);
        return *this;
    }

    CircleShape build() {
        return shape;
    }
};

unsigned int screen_width = 640, screen_height = 400;

void resolveCollision(CircleShape &shape, Vector2f &vel) {
    FloatRect shape_bounds = shape.getGlobalBounds();
    if (shape_bounds.height + shape_bounds.top >= screen_height) {
        shape.setPosition(shape.getPosition().x, screen_height - shape_bounds.height);
        vel.y *= -1.f * 0.8f;
    }
}

int main()
{
    RenderWindow window(VideoMode(screen_width, screen_height), "binbow", Style::Default);
    window.setFramerateLimit(60);

    Vector2f velocity = Vector2f(0.f, 0.f);
    Vector2f gravity = Vector2f(0.f, 9.8f);
    ShapeBuilder builder;
    CircleShape shape = builder
                            .setColor(0, 100, 255)
                            .setPosition(screen_width/2 - 10, screen_height/2 - 10)
                            .setSize(10.f)
                            .build();

    while (window.isOpen()) {
        Event event;

        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed) {
                switch (event.key.code) {
                case Keyboard::W:
                    shape.move(Vector2f(0.f, -10.f));
                    break;
                case Keyboard::A:
                    shape.move(Vector2f(-10.f, 0.f));
                    break;
                case Keyboard::S:
                    shape.move(Vector2f(0.f, 10.f));
                    break;
                case Keyboard::D:
                    shape.move(Vector2f(10.f, 0.f));
                    break;
                default:
                    break;
                }
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape))
            window.close();

        // update
        window.clear();

        // change stuff here

        velocity.y += gravity.y * 1/60;

        shape.setPosition(shape.getPosition() + velocity);
        resolveCollision(shape, velocity);

        window.draw(shape);

        // draw everything
        window.display();
    }


    return 0;
}