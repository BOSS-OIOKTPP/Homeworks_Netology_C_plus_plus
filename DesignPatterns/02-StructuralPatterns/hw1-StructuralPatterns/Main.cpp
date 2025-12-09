#include <iostream>
#include <windows.h>
#include <string>

// Базовый класс
class Text {
public:
    virtual void render(const std::string& data) const {
        std::cout << data;
    }
};


class DecoratedText : public Text {
public:
    explicit DecoratedText(Text* text) : text_(text) {}
    Text* text_;
};

class ItalicText : public DecoratedText {
public:
    explicit ItalicText(Text* text) : DecoratedText(text) {}
    void render(const std::string& data)  const {
        std::cout << "<i>";
        text_->render(data);
        std::cout << "</i>";
    }
};

class BoldText : public DecoratedText {
public:
    explicit BoldText(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const {
        std::cout << "<b>";
        text_->render(data);
        std::cout << "</b>";
    }
};


// Новые классы
class Paragraph : public DecoratedText {
public:
    explicit Paragraph(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const {
        std::cout << "<p>";
        text_->render(data);
        std::cout << "</p>";
    }
};

class Reversed : public DecoratedText {
public:
    explicit Reversed(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const {
        std::string tmp = data;
        std::reverse(tmp.begin(), tmp.end());
        text_->render(tmp);
    }
};

class Link : public DecoratedText {
public:
    explicit Link(Text* text) : DecoratedText(text) {}   
    void render(const std::string& href, const std::string& data) const {
        std::cout << "<a href=" << href << ">";
        text_->render(data);
        std::cout << "</a>";
    }
};



int main() {
    // Установка кодировки консоли Windows
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::cout << "1. Paragraph:\n";
    auto text_block1 = new Paragraph(new Text());
    text_block1->render("Hello world");
    std::cout << "\n\n";
    delete text_block1;

    std::cout << "2. Reversed:\n";
    auto text_block2 = new Reversed(new Text());
    text_block2->render("Hello world");
    std::cout << "\n\n";
    delete text_block2;

    std::cout << "3. Link:\n";
    auto text_block3 = new Link(new Text());
    text_block3->render("netology.ru", "Hello world");
    std::cout << "\n\n";
    delete text_block3;

    std::cout << std::endl;
    system("pause");

    return EXIT_SUCCESS;
}

