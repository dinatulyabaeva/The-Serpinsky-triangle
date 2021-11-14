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
    int counter = 0;  // счетчик кликов
    sf::VertexArray triangle(sf::LinesStrip, 4);    // класс для массива вершин
    sf::CircleShape circle(800 / 500); //класс для круга
    circle.setFillColor(sf::Color::White);
    sf::Vector2f point;   // текущая точка. класс для определения вектора

    while (window.isOpen())
    {
        sf::Event event;     // объект события
        while (window.pollEvent(event)) //обработка событий
        {
            switch (event.type)
            {
                // если произошло событие закрытия окна, то закрыть
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonPressed:
                // если пользователь нажал на левую кнопку мыши
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

        // рисует треугольник и текущую точку
        if (counter == 3)
        {
            window.draw(triangle);
            drawCircle(window, point, circle);
            // перемещает текущую точку
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

// генерирует случайное число от low до high
int RandomInteger(int low, int high)
{
    double normalVal = double(rand()) / (double(RAND_MAX) + 1);
    int scaledVal = int(normalVal * (high - low + 1)); //масштабное значение
    return low + scaledVal;
}


// рисует круг с центром в текущей точке
void drawCircle(sf::RenderWindow& window, sf::Vector2f currentPoint, sf::CircleShape& circle)
{
    circle.setFillColor(sf::Color(sf::Color::White));
    int xPos = currentPoint.x - circle.getRadius(); //circle - круг
    int yPos = currentPoint.y - circle.getRadius();
    //cout << "Random x: " << xPos + circle.getRadius() << " y: " << yPos + circle.getRadius() << endl;
    circle.setPosition(xPos, yPos);
    window.draw(circle);
}

// перемещает текущую точку в направлении случайно выбранной вершины на половину расстояния до вершины
void moveCurrentPoint(sf::Vector2f& currentPoint, sf::VertexArray triangle)
{
    int vertex = RandomInteger(0, 2); //вершина
    sf::Vector2f dirVertex = triangle[vertex].position;
    currentPoint.x = (dirVertex.x + currentPoint.x) / 2;
    currentPoint.y = (dirVertex.y + currentPoint.y) / 2;
}