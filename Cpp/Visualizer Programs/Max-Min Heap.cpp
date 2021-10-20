#include <iostream>
#include <queue>
#include <math.h>
#include <SFML/Graphics.hpp>

sf::RenderWindow window(sf::VideoMode(1377, 768), "Heap");

using namespace std;

class Heap
{
    int *arr, capacity, heapSize, data = 0;
    sf::Font font;
    sf::Text text;
    sf::RectangleShape line, rect;
    sf::CircleShape circle;

public:
    Heap(const int &capacity) : heapSize(0), capacity(capacity)
    {
        if (!font.loadFromFile("impact.ttf"))
            std::cout << "Font Not Found!\n";
        arr = new int[capacity];
    }
    int insertNode(const int &data)
    {
        if (heapSize == capacity) // ? Checks if the array is now full
            return -1;
        heapSize++;
        int index = heapSize - 1;
        arr[index] = data;
        cout << "[+] Node has been successfully added!\n";
        heapify(index);
        return 0;
    }
    inline void displayBoth()
    {
        if (arr[0] == '\0')
            return;
        int x = 50, y = 0, barrier = window.getSize().x / 2;
        window.draw(statement(text, "InOrder Traversal", 25, window.getSize().y - 100));
        window.draw(statement(text, "LevelOrder Traversal", window.getSize().x - 200, window.getSize().y - 110));
        window.draw(createBoundary(line));
        maxHeapify(0);
        showInOrder(0, x, y, 50, barrier);
        x = (window.getSize().x) / 2 + 200, y = 0, barrier = window.getSize().x - 10;
        minHeapify(0);
        showInOrder(0, x, y, (window.getSize().x / 2) + 75, barrier);
    }
    void minHeapify(const int &index)
    {
        int left = this->left(index), right = this->right(index), smallest = index;
        if (left < heapSize && arr[left] < arr[index])
            smallest = left;
        if (right < heapSize && arr[right] < arr[smallest])
            smallest = right;
        if (smallest != index)
            swap(arr[index], arr[smallest]), maxHeapify(smallest);
        cout << "[+] Tree has been successfully converted to min heap\n";
    }
    void maxHeapify(const int &index)
    {
        int left = this->left(index), right = this->right(index), largest = index;
        if (left < heapSize && arr[left] > arr[index])
            largest = left;
        if (right < heapSize && arr[right] > arr[largest])
            largest = right;
        if (largest != index)
            swap(arr[index], arr[largest]), maxHeapify(largest);
        cout << "[+] Tree has been successfully converted to max heap\n";
    }

private:
    // NOTE Circular Array Type Implementation
    inline int left(const int &index)
    {
        if (arr[index] != '\0' && ((2 * index) + 1) < heapSize)
            return (2 * index + 1);
        return -1;
    }
    inline int right(const int &index)
    {
        if (arr[index] != '\0' && ((2 * index) + 2) < heapSize)
            return (2 * index + 2);
        return -1;
    }
    inline int parent(const int &index)
    {
        if (arr[index] != '\0' && ((index - 1) / 2) < heapSize && (index - 1) / 2 > -1)
            return ((index - 1) / 2);
        return -1;
    }
    // END Note
    void heapify(int &index) // ? Simple function to iteratively check and sort the array
    {
        while (arr[parent(index)] < arr[index] && arr[index] != '\0' && arr[parent(index)] != '\0' && index > -1 && index < heapSize)
            swap(arr[index], arr[parent(index)]), index = parent(index);
    }

    void printNodes(const int &index, const int &x, const int &y)
    {
        if (arr[left(index)] == '\0' && arr[right(index)] == '\0')
        {
            circle = createCircle(circle, x, y);
            circle.setFillColor(sf::Color(30, 144, 255));
            circle.setOutlineColor(sf::Color::Red);
            window.draw(circle);
        }
        else if (left(index) != '\0' && right(index) != '\0')
        {
            sf::RectangleShape leftLine, rightLine;
            leftLine = createLine(line, arr[index]), rightLine = createLine(line, arr[index]);
            rightLine.setPosition((circle.getPosition().x + circle.getRadius() / 2) + 33, circle.getPosition().y + circle.getRadius());
            rightLine.setRotation(45);
            leftLine.setPosition((circle.getPosition().x + circle.getRadius() / 2) - 15, circle.getPosition().y + circle.getRadius());
            leftLine.setRotation(135);
            window.draw(createCircle(circle, x, y));
            window.draw(leftLine);
            window.draw(rightLine);
        }
        else
            window.draw(createCircle(circle, x, y));
        window.draw(createText(arr[index], x, y));
        window.draw(createLine(line, arr[index]));
        data = arr[index];
    }
    void showInOrder(const int &index, int &x, int &y, const int &door, const int &barrier, int level = 1)
    {
        if (x >= barrier)
            x = door, window.clear();
        y = 0;
        if (arr[index] != '\0')
        {
            showInOrder(left(index), x, y, door, barrier, level + 1);
            for (int i = 0; i < level && arr[index] != '\0'; i++)
                y += 50;
            printNodes(index, x, y);
            x += 50;
            showInOrder(right(index), x, y, door, barrier, level + 1);
        }
    }
    inline sf::RectangleShape createBoundary(sf::RectangleShape &line)
    {
        line.setSize(sf::Vector2f(10, window.getSize().y));
        line.setFillColor(sf::Color::Red);
        line.setPosition(window.getSize().x / 2, 0);
        line.setRotation(360);
        return line;
    }
    inline sf::Text statement(sf::Text &text, const std::string &statement, const int &x, const int &y)
    {
        text.setFont(font);
        text.setFillColor(sf::Color::White);
        text.setCharacterSize(20);
        text.setString(statement);
        text.setPosition(x, y);
        return text;
    }
    inline sf::RectangleShape createLine(sf::RectangleShape &line, const int &currentData)
    {
        line.setSize(sf::Vector2f(50, 2));
        line.setFillColor(sf::Color::Cyan);
        if (currentData > data)
        {
            line.setPosition((circle.getPosition().x + circle.getRadius() / 2) + 33, circle.getPosition().y + circle.getRadius());
            line.setRotation(45);
        }
        else if (currentData <= data)
        {
            line.setPosition((circle.getPosition().x + circle.getRadius() / 2) - 15, circle.getPosition().y + circle.getRadius());
            line.setRotation(135);
        }
        return line;
    }
    inline sf::CircleShape createCircle(sf::CircleShape &circle, const int &x, const int &y)
    {
        circle.setFillColor(sf::Color::Blue);
        circle.setOutlineColor(sf::Color::Cyan);
        circle.setOutlineThickness(2);
        circle.setRadius(20);
        circle.setPosition(sf::Vector2f(x, y));
        return circle;
    }
    inline sf::Text createText(const int &data, const int &x, const int &y)
    {
        text.setFont(font);
        text.setFillColor(sf::Color::White);
        text.setCharacterSize(20);
        text.setString(std::to_string(data));
        text.setPosition(x + 13, y + 7);
        return text;
    }
};
static void mainMenu()
{
    int capacity, opt, number;
    cout << "Enter Total Capacity: ";
    cin >> capacity;
    Heap obj(capacity);
loop:
    cout << "0. Insert Node\n1. Display Both\n2. Exit\n";
    cout << "Option > ";
    cin >> opt;
    switch (opt)
    {
    case 0:
        cout << "Enter Data: ";
        cin >> number;
        if (obj.insertNode(number) == -1)
            cout << "Array is Full!\n";
        window.clear();
        break;
    case 1:
        obj.displayBoth();
        window.display();
        break;
    case 2:
        exit(0);
        break;
    default:
        cout << "[-] The Option is out of bounds, Please try again\n";
        break;
    }
    goto loop;
}

int main()
{
    mainMenu();
}