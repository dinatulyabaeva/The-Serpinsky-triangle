#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

void Randomize();
int RandomInteger(int low, int high);
void drawCircle(sf::RenderWindow& window, sf::Vector2f currentPoint, sf::CircleShape& circle);
void moveCurrentPoint(sf::Vector2f& currentPoint, sf::VertexArray triangle);
int main()
{
    Randomize();
    sf::RenderWindow window(sf::VideoMode(800, 600), "The Serpinsky triangle");
    int counter = 0;  // ������� ������
    sf::VertexArray triangle(sf::LinesStrip, 4);    // ����� ��� ������� ������
    sf::CircleShape circle(800 / 500); //����� ��� �����
    circle.setFillColor(sf::Color::White);
    sf::Vector2f point;   // ������� �����. ����� ��� ����������� �������

    while (window.isOpen())
    {
        sf::Event event;     // ������ �������
        while (window.pollEvent(event)) //��������� �������
        {
            switch (event.type)
            {
                // ���� ��������� ������� �������� ����, �� �������
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonPressed:
                // ���� ������������ ����� �� ����� ������ ����
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (counter <= 2)
                        triangle[counter].position = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
                    counter++;
                    if (counter == 3)
                    {
                        triangle[counter].position = triangle[0].position;
                        point = triangle[RandomInteger(0, 2)].position;
                    }
                }
                break;
            }
        }

        // ������ ����������� � ������� �����
        if (counter == 3)
        {
            window.draw(triangle);
            drawCircle(window, point, circle);
            // ���������� ������� �����
            moveCurrentPoint(point, triangle);
        }
        else if (counter > 3) window.close();
        window.display();
    }

    return 0;
}

void Randomize()
{
    srand(int(time(NULL)));
}

// ���������� ��������� ����� �� low �� high
int RandomInteger(int low, int high)
{
    double normalVal = double(rand()) / (double(RAND_MAX) + 1);
    int scaledVal = int(normalVal * (high - low + 1)); //���������� ��������
    return low + scaledVal;
}


// ������ ���� � ������� � ������� �����
void drawCircle(sf::RenderWindow& window, sf::Vector2f currentPoint, sf::CircleShape& circle)
{
    circle.setFillColor(sf::Color(sf::Color::White));
    int xPos = currentPoint.x - circle.getRadius(); //circle - ����
    int yPos = currentPoint.y - circle.getRadius();
    //cout << "Random x: " << xPos + circle.getRadius() << " y: " << yPos + circle.getRadius() << endl;
    circle.setPosition(xPos, yPos);
    window.draw(circle);
}

// ���������� ������� ����� � ����������� �������� ��������� ������� �� �������� ���������� �� �������
void moveCurrentPoint(sf::Vector2f& currentPoint, sf::VertexArray triangle)
{
    int vertex = RandomInteger(0, 2); //�������
    sf::Vector2f dirVertex = triangle[vertex].position;
    currentPoint.x = (dirVertex.x + currentPoint.x) / 2;
    currentPoint.y = (dirVertex.y + currentPoint.y) / 2;
}