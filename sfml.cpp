#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <random>
#include <thread>
#include <chrono>
using namespace std;
using namespace sf;
using namespace chrono;

class Line
{
    RectangleShape rectangle;
    Vector2f p1, p2;
    double length;
    double width = 1;
    double pi = 3.1415926;

    void setLine(Vector2f p1, Vector2f p2)
    {
        this->p1 = p1;
        this->p2 = p2;

        length = sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));

        rectangle.setPosition(p1);
        rectangle.setSize(Vector2f(length, width));

        double rotation = (180 / pi) * acos((p2.x - p1.x) / length);

        cout << rotation << endl;

        if (p2.x > p1.x) rectangle.setRotation(rotation);
        else rectangle.setRotation(-rotation);
    }

public:

    Line(Vector2f p1, Vector2f p2): p1(p1), p2(p2)
    { 
        setLine(p1, p2);
    }

    Line() = default;

    void setP1(Vector2f p1)
    {
        setLine(p1, p2);
    }

    void setP2(Vector2f p2)
    {
        setLine(p1, p2);
    }

    Vector2f getP1()
    {
        return p1;
    }

    Vector2f getP2()
    {
        return p2;
    }

    RectangleShape getLine()
    {
        return rectangle;
    }
};

int main()
{
    int winX = 800, winY = 600;

    sf::RenderWindow window(sf::VideoMode(winX, winY), "My window");
    Vector2f p1(100, 100), p2(200, 200);
    Line line(p1, p2);

    Font font;
    Text text;
    string text_str = "p1: " + to_string(p1.x) + " " + to_string(p1.y) + "\n" + "p2: " + to_string(p2.x) + " " + to_string(p2.y);

    font.loadFromFile("arial.ttf");

    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(Color::White);
    text.setPosition(Vector2f(0, 0));
    text.setString(text_str);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear(sf::Color::Black);

        window.draw(line.getLine());
        window.draw(text);

        window.display();

        string point;
        double x, y;

        cin >> point >> x >> y;

        if (point == "p1")
        {
            line.setP1(Vector2f(x, y));
        }
        else if (point == "p2")
        {
            line.setP2(Vector2f(x, y));
        }

        text_str = "p1: " + to_string(line.getP1().x) + " " + to_string(line.getP1().y) + "\n" + "p2: " + to_string(line.getP2().x) + " " + to_string(line.getP2().y);
        text.setString(text_str);
    }
}