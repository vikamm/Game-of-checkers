#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <windows.h>

#define W_PAWN 1000 
#define W_PAWN_DAMKA 5000 
using namespace std;
vector<vector<int>> figure(9);
vector<vector<int>> raskraska(9);
vector <pair<int, int>> all;
vector<vector<vector<int>>> figure_pred;

int usl_vuigr = 0;
int for_robot = 0;

int hod = 0;
int size = 65;
void raskr() {
    raskraska[1].resize(9);
    raskraska[1][2] = 1;
    raskraska[1][4] = 1;
    raskraska[1][6] = 1;
    raskraska[1][8] = 1;
    raskraska[1][1] = 2;
    raskraska[1][3] = 2;
    raskraska[1][5] = 2;
    raskraska[1][7] = 2;

    figure[1].resize(9);

    for (int i = 2; i <= 8; ++i) {
        raskraska[i].resize(9);
        figure[i].resize(9);
        for (int j = 1; j <= 8; ++j) {
            if (raskraska[i - 1][j] == 2) {
                raskraska[i][j] = 1;
            }
            else {
                raskraska[i][j] = 2;
            }
        }
    }
    for (int i = 1; i <= 8; ++i) {
        for (int j = 1; j <= 8; ++j) {
            if (raskraska[i][j] == 2 && i <= 3) {
                figure[i][j] = 2;
            }
            if (raskraska[i][j] == 2 && i >= 6) {
                figure[i][j] = 1;
            }
        }
    }
    for (int i = 4; i <= 5; ++i) {
        for (int j = 1; j <= 8; ++j) {
            figure[i][j] = 0;
        }
    }
}

void check_choose(int x, int y) {
    cout << "ok" << hod;
    if (x <= 8 && y <= 8 && figure[y][x] != 0 && figure[y][x] % 2 == hod % 2) {
        if (x >= 1 && x <= 8 && y >= 1 && y <= 8) {
            hod += 1;
            bool flag = 0;
            if (x - 1 >= 1 && y - 1 >= 1 && figure[y - 1][x - 1] != figure[y][x]) {
                if (figure[y - 1][x - 1] != 0) {
                    if (y - 2 >= 1 && x - 2 >= 1 && figure[y - 2][x - 2] == 0) {
                        all.push_back(make_pair(x - 2, y - 2));
                        flag = 1;
                    }
                }
            }
            if (x + 1 <= 8 && y - 1 >= 1 && figure[y - 1][x + 1] != figure[y][x]) {
                if (figure[y - 1][x + 1] != 0) {
                    if (y - 2 >= 1 && x + 2 <= 8 && figure[y - 2][x + 2] == 0) {
                        all.push_back(make_pair(x + 2, y - 2));
                        flag = 1;
                    }
                }
            }
            if (!flag) {
                if (x + 1 <= 8 && y + 1 <= 8 && figure[y + 1][x + 1] != figure[y][x]) {
                    if (figure[y + 1][x + 1] == 0) {
                        all.push_back(make_pair(x + 1, y + 1));
                    }
                    else {
                        if (y + 2 <= 8 && x + 2 <= 8 && figure[y + 2][x + 2] == 0) {
                            all.push_back(make_pair(x + 2, y + 2));
                        }
                    }
                }
                if (x - 1 >= 1 && y + 1 <= 8 && figure[y + 1][x - 1] != figure[y][x]) {
                    if (figure[y + 1][x - 1] == 0) {
                        all.push_back(make_pair(x - 1, y + 1));
                    }
                    else {
                        if (y + 2 <= 8 && x - 2 >= 1 && figure[y + 2][x - 2] == 0) {
                            all.push_back(make_pair(x - 2, y + 2));
                        }
                    }
                }
            }
        }
       
    }
}

vector<pair<int, int>> get_hod(int x, int y, int color) {
    vector<pair<int, int>> prom;
    if (figure[y][x] != 0 && figure[y][x] == color) {
        if (x >= 1 && x <= 8 && y >= 1 && y <= 8) {
            if (color == 2) {
                bool flag = 0;
                if (x - 1 >= 1 && y - 1 >= 1 && figure[y - 1][x - 1] != figure[y][x]) {
                    if (figure[y - 1][x - 1] != 0) {
                        if (y - 2 >= 1 && x - 2 >= 1 && figure[y - 2][x - 2] == 0) {
                            prom.push_back(make_pair(x - 2, y - 2));
                            flag = 1;
                        }
                    }
                }
                if (x + 1 <= 8 && y - 1 >= 1 && figure[y - 1][x + 1] != figure[y][x]) {
                    if (figure[y - 1][x + 1] != 0) {
                        if (y - 2 >= 1 && x + 2 <= 8 && figure[y - 2][x + 2] == 0) {
                            prom.push_back(make_pair(x + 2, y - 2));
                            flag = 1;
                        }
                    }
                }
                if (!flag) {
                    if (x + 1 <= 8 && y + 1 <= 8 && figure[y + 1][x + 1] != figure[y][x]) {
                        if (figure[y + 1][x + 1] == 0) {
                            prom.push_back(make_pair(x + 1, y + 1));
                        }
                        else {
                            if (y + 2 <= 8 && x + 2 <= 8 && figure[y + 2][x + 2] == 0) {
                                prom.push_back(make_pair(x + 2, y + 2));
                            }
                        }
                    }
                    if (x - 1 >= 1 && y + 1 <= 8 && figure[y + 1][x - 1] != figure[y][x]) {
                        if (figure[y + 1][x - 1] == 0) {
                            prom.push_back(make_pair(x - 1, y + 1));
                        }
                        else {
                            if (y + 2 <= 8 && x - 2 >= 1 && figure[y + 2][x - 2] == 0) {
                                prom.push_back(make_pair(x - 2, y + 2));
                            }
                        }
                    }
                }
            }
            else {
                bool flag = 0;
                if (x - 1 >= 1 && y + 1 <= 8 && figure[y + 1][x - 1] != figure[y][x]) {
                    if (figure[y + 1][x - 1] != 0) {
                        if (y + 2 <= 8 && x - 2 >= 1 && figure[y + 2][x - 2] == 0) {
                            prom.push_back(make_pair(x - 2, y + 2));
                            flag = 1;
                        }
                    }
                }
                if (x + 1 <= 8 && y + 1 <= 8 && figure[y + 1][x + 1] != figure[y][x]) {
                    if (figure[y + 1][x + 1] != 0) {
                        if (y + 2 <= 8 && x + 2 <= 8 && figure[y + 2][x + 2] == 0) {
                            prom.push_back(make_pair(x + 2, y + 2));
                            flag = 1;
                        }
                    }
                }
                if (!flag) {
                    if (x + 1 <= 8 && y - 1 >= 1 && figure[y - 1][x + 1] != 1) {
                        if (figure[y - 1][x + 1] == 0) {
                            prom.push_back(make_pair(x + 1, y - 1));
                        }
                        else {
                            if (y - 2 >= 1 && x + 2 <= 8 && figure[y - 2][x + 2] == 0) {
                                prom.push_back(make_pair(x + 2, y - 2));
                            }
                        }
                    }
                    if (x - 1 >= 1 && y - 1 >= 1 && figure[y - 1][x - 1] != 1) {
                        if (figure[y - 1][x - 1] == 0) {
                            prom.push_back(make_pair(x - 1, y - 1));
                        }
                        else {
                            if (y - 2 >= 1 && x - 2 >= 1 && figure[y - 2][x - 2] == 0) {
                                prom.push_back(make_pair(x - 2, y - 2));
                            }
                        }
                    }
                }
            }
        }
    }
    return prom;
}

int xnow = 0, ynow = 0;
int white = 0, black = 0;
void go_to(int x, int y) {
    if (!(ynow == y && xnow == x)) {
        if (abs(y - ynow) == 2 && abs(x - xnow) == 2) {
            figure[y][x] = figure[ynow][xnow];
            if (x > xnow && y > ynow) {
                figure[ynow + 1][xnow + 1] = 0;
            }
            if (x < xnow && y > ynow) {
                figure[ynow + 1][xnow - 1] = 0;
            }
            if (x > xnow && y < ynow) {
                figure[ynow - 1][xnow + 1] = 0;
            }
            if (x < xnow && y < ynow) {
                figure[ynow - 1][xnow - 1] = 0;
            } 
            figure[ynow][xnow] = 0;
        }
        else {
            figure[y][x] = figure[ynow][xnow];
            figure[ynow][xnow] = 0;
        }
    }
}

int matrixw[9][9];
int matrixb[9][9];

void zapoln() {
    for (int i = 1; i <= 8; ++i) {
        for (int j = 1; j <= 8; ++j) {
            if (i == 8) {
                matrixw[i][j] = 2000;
            }
            if (i == 7) {
                matrixw[i][j] = 1600;
            }
            if (i == 6) {
                matrixw[i][j] = 1000;
            }
            if (i >= 4 && i <= 5) {
                matrixw[i][j] = 600;
            }
            if (i < 4) {
                matrixw[i][j] = 200;
            }
        }
    }
    for (int i = 1; i <= 8; ++i) {
        for (int j = 1; j <= 8; ++j) {
            if (i == 1) {
                matrixb[i][j] = 2000;
            }
            if (i == 2) {
                matrixb[i][j] = 1600;
            }
            if (i == 3) {
                matrixb[i][j] = 1000;
            }
            if (i >= 4 && i <= 5) {
                matrixb[i][j] = 600;
            }
            if (i > 5) {
                matrixb[i][j] = 200;
            }
        }
    }
}

int Evaluate(int color) {
    int now1 = 0, now2 = 0;
    int count1 = 0, count2 = 0;
    for (int i = 1; i <= 8; ++i) {
        for (int j = 1; j <= 8; ++j) {
            if (figure[i][j] == color) {
                count1 += 1;
                if(color == 1) {
                   now1 += matrixb[i][j];
                }
                else {
                    now1 += matrixw[i][j];
                }
            }
            else {
                if (figure[i][j] != 0) {
                    count2 += 1;
                    if (color == 1) {
                        now2 += matrixb[i][j];
                    }
                    else {
                        now2 += matrixw[i][j];
                    }
                }
            }
        }
    }
    return now1 - now2;
}



void count() {
    white = 0;
    black = 0;
    for (int i = 1; i <= 8; ++i) {
        for (int j = 1; j <= 8; ++j) {
            if (figure[i][j] == 1) {
                black += 1;
            }
            else {
                if (figure[i][j] == 2) {
                    white += 1;
                }
            }
        }
    }
}

int64_t max_score = 0;
vector<pair<int, pair<int,int>>> posl_score_hod;


void go_to_robot(int x1, int y1, int x, int y) {
    if (!(y1 == y && x1 == x)) {
        if (abs(y - y1) == 2 && abs(x - x1) == 2) {
            figure[y][x] = figure[y1][x1];
            if (x > x1 && y1 < y) {
                figure[y1 + 1][x1 + 1] = 0;
            }
            if (x > x1 && y1 > y) {
                figure[y1 - 1][x1 + 1] = 0;
            }
            if (x < x1 && y1 < y) {
                figure[y1 + 1][x1 - 1] = 0;
            }
            if (x < x1 && y1 > y) {
                figure[y1 - 1][x1 - 1] = 0;
            }
            figure[y1][x1] = 0;
        }
        else {
            figure[y][x] = figure[y1][x1];
            figure[y1][x1] = 0;
        }
    }
}

int depth_ = 10;
vector <pair<pair<int, int>, pair<int, int>>>  all_hod;

vector<pair<int, vector <pair<pair<int, int>, pair<int, int>>>>> all_current;
vector <pair<pair<int, int>, pair<int, int>>> current;
pair<pair<int, int>, pair<int, int>> besty_h;
pair<pair<int, int>, pair<int, int>> noww;
int maxim_now = -INT_MAX;

int64_t  AlphaBeta(int color, int depth, int alpha, int beta) {
    int score = -INT_MAX;
    vector <pair<pair<int, int>, pair<int, int>>> move;
    if (depth == 0) {
        int64_t now = Evaluate(color);
        return now;
    }
    for (int i = 1; i <= 8; ++i) {
        for (int j = 1; j <= 8; ++j) {
            if (figure[i][j] == color) {
                vector<pair<int,int>> mooooo = get_hod(j, i, color);
                for (int l = 0; l < mooooo.size(); ++l) {
                    move.push_back(make_pair(make_pair(j, i), mooooo[l]));
                }
            }
        }
    }
    while (move.size() > 0) {
        int x = move[0].first.first;
        int y = move[0].first.second;
        int x1 = move[0].second.first;
        int y1 = move[0].second.second;
        if (depth == depth_) {
            noww = { {x, y}, {x1, y1} };
        }
        if (color == 1 && depth == depth_) {
            current.push_back(make_pair(make_pair(x, y), make_pair(x1, y1)));
        }
        vector<vector<int>> prom = figure;
        go_to_robot(x, y, x1, y1); 
        int tmp = -AlphaBeta(3-color, depth - 1, -beta, -alpha);
        if (tmp > maxim_now && depth == depth_) {
            all_current.push_back(make_pair(alpha, current));
            current.clear();
            maxim_now = tmp;
            besty_h = noww;
        }
        figure = prom;
        if (tmp > score) {
            score = tmp;
        }
        if (score > alpha) {
            alpha = score;
        }
        if (alpha >= beta) {
            return alpha;
        }
        move.erase(move.begin());
    }
    all_current.push_back(make_pair(score, current));
    current.clear();
    return score;
}

bool endi = 0;

void outset() {
    int color = 0;
    for (int j = 1; j <= 8; ++j) {
        if (figure[1][j] == 1) {
            color = 1;
        }
    }
    for (int j = 1; j <= 8; ++j) {
        if (figure[8][j] == 2) {
            color = 2;
        }
    }
    if (color != 0) {
        for (int i = 1; i <= 8; ++i) {
            for (int j = 1; j <= 8; ++j) {
                cout << figure[i][j] << " ";
            }
            cout << endl;
        }
    }
    if (color == 0) {
        return;
    }

    setlocale(LC_ALL, "Rus");
    setlocale(LC_ALL, "");
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    sf::RenderWindow window(sf::VideoMode(600, 300), "INPUT");
    sf::Font font;
    if (!font.loadFromFile("D:/праки/play_checkers/ofont.ru_Zeitmax.ttf")) {
        std::cout << "error";
    }
    sf::Image start;
    start.loadFromFile("D:/файлы программирование/png-klev-club-pmxl-p-pryamougolnaya-knopka-png-25.png");
    sf::Texture start_;
    start_.loadFromImage(start);
    sf::Sprite start0_;
    start0_.setTexture(start_);
    start0_.setPosition(130, 260);
    start0_.scale(sf::Vector2f(0.1, 0.1));

    sf::Image start2;
    start2.loadFromFile("D:/файлы программирование/png-klev-club-pmxl-p-pryamougolnaya-knopka-png-25.png");
    sf::Texture start2_;
    start2_.loadFromImage(start2);
    sf::Sprite start20_;
    start20_.setTexture(start2_);
    start20_.setPosition(130, 400);
    start20_.scale(sf::Vector2f(0.1, 0.1));


    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(56);
    text.setFillColor(sf::Color(240, 0, 0));
    text.setPosition(20, 100);
    if (color == 2) {
        text.setString(L"Белые победили!");
    }
    else {
        text.setString(L"Чёрные победили!");
    }
    sf::Text text0;
    text0.setFont(font);
    text0.setCharacterSize(56);
    text0.setFillColor(sf::Color(40, 40, 40));
    text0.setPosition(22, 102);
    if (color == 2) {
        text0.setString(L"Белые победили!");
    }
    else {
        text0.setString(L"Чёрные победили!");
    }
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                window.close();
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2i position = sf::Mouse::getPosition(window);
                int x_ = position.x, y_ = position.y;
            }
        }
        window.draw(text);
        window.draw(text0);
        window.display();
        window.clear();
    }
}

int nowx = 0, nowy = 0, nowxto = 0, nowyto = 0;

void all_generations(int color) {
    maxim_now = -INT_MAX;
    all_current.clear();
    current.clear();
    max_score = -INT_MAX;
    int bestx = 0, besty = 0;
    vector<vector<int>> promet = figure;
    int64_t nowr;
    nowr = AlphaBeta(color, depth_, -INT_MAX, INT_MAX);
   
    figure = promet;
    int bestx_to = 0, besty_to = 0;

    for (int i = 1; i <= 8; i += 7) {
        int fl = 1;
        for (int j = 1; j <= 8; ++j) {
            if (figure[i][j] == 0) {
                fl = 0;
            }
        }
        if (fl == 1) {
            if (i == 1) {
                usl_vuigr = 2;
            }
            else {
                usl_vuigr = 1;
            }
        }
    }
    bestx = besty_h.first.first;
    besty = besty_h.first.second;
    bestx_to = besty_h.second.first;
    besty_to = besty_h.second.second;
    all_hod.push_back({ {besty_h.first.first, besty_h.first.second}, {besty_h.second.first, besty_h.second.second} });
    go_to_robot(bestx, besty, bestx_to, besty_to);
    figure_pred.push_back(figure);
    outset();
}

bool regim_play = 0;


void isx() {
    setlocale(LC_ALL, "Rus");
    setlocale(LC_ALL, "");
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    sf::RenderWindow window(sf::VideoMode(600, 600), "INPUT");
    sf::Font font;
    if (!font.loadFromFile("D:/праки/play_checkers/ofont.ru_Zeitmax.ttf")) {
        std::cout << "error";
    }
    sf::Image start;
    start.loadFromFile("D:/файлы программирование/png-klev-club-pmxl-p-pryamougolnaya-knopka-png-25.png");
    sf::Texture start_;
    start_.loadFromImage(start);
    sf::Sprite start0_;
    start0_.setTexture(start_);
    start0_.setPosition(130, 260);
    start0_.scale(sf::Vector2f(0.1, 0.1));

    sf::Image start2;
    start2.loadFromFile("D:/файлы программирование/png-klev-club-pmxl-p-pryamougolnaya-knopka-png-25.png");
    sf::Texture start2_;
    start2_.loadFromImage(start2);
    sf::Sprite start20_;
    start20_.setTexture(start2_);
    start20_.setPosition(130, 400);
    start20_.scale(sf::Vector2f(0.1, 0.1));


    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(56);
    text.setFillColor(sf::Color(240, 0, 0));
    text.setPosition(20, 100);
    text.setString(L"Выберите режим:");
    sf::Text text0;
    text0.setFont(font);
    text0.setCharacterSize(56);
    text0.setFillColor(sf::Color(40, 40, 40));
    text0.setPosition(22, 102);
    text0.setString(L"Выберите режим:");

    sf::Text text1;
    text1.setFont(font);
    text1.setCharacterSize(40);
    text1.setFillColor(sf::Color(0, 0, 0));
    text1.setPosition(190, 300);
    text1.setString(L"Вы VS Бот");

    sf::Text text2;
    text2.setFont(font);
    text2.setCharacterSize(40);
    text2.setFillColor(sf::Color(0, 0, 0));
    text2.setPosition(186, 440);
    text2.setString(L"Бот VS Бот");


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                window.close();
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2i position = sf::Mouse::getPosition(window);
                int x_ = position.x, y_ = position.y;
                if (x_ >= 130 && x_ <= 400 && y_ >= 260 && y_ <= 360) {
                    regim_play = 0;
                    return;
                }
                if (x_ >= 130 && x_ <= 400 && y_ >= 400 && y_ <= 560) {
                    regim_play = 1;
                    return;
                }
            }
        }
        window.draw(text);
        window.draw(text0);
        window.draw(start0_);
        window.draw(start20_);
        window.draw(text1);
        window.draw(text2);
        window.display();
        window.clear();
    }
}

bool hod_nazad(int x, int y) {
    if (x >= 110 && x <= 200 && y >= 634 && y <= 674 && figure_pred.size()>=2) {
        hod -= 2;
        figure = figure_pred[figure_pred.size() - 3];
        figure_pred.pop_back();
        figure_pred.pop_back();
        all_hod.pop_back();
        all_hod.pop_back();
        return 1;
    }
    return 0;
}

#include <fstream>

void check_zapis(int x, int y) {
    if (x >= 546 && x <= 646 && y >= 634 && y <= 674) {
        std::ofstream out; 
        out.open("D:/праки/play_checkers/down.txt");
        out << hod << std::endl;
        for (int i = 1; i <= 8; ++i) {
            for (int j = 1; j <= 8; ++j) {
                out << figure[i][j] << " ";
            }
            out << endl;
        }
        out.close();
        figure_pred.push_back(figure);
    }
}

bool podsazka_need = 0;

void  check_skach(int x, int y) {
    if (x >= 400 && x <= 500 && y >= 634 && y <= 674) {

        std::ifstream in;
        in.open("D:/праки/play_checkers/down.txt");
        string pr;
        in >> pr;
        hod = stoi(pr);
        for (int i = 1; i <= 8; ++i) {
            for (int j = 1; j <= 8; ++j) {
                in >> figure[i][j];
            }
        }
        in.close();
    }
}

int bx = 0, by = 0, btx = 0, bty = 0;

void check_podsk(int x, int y) {
    if (x >= 200 && x <= 300 && y >= 634 && y <= 674) {
        maxim_now = -INT_MAX;
        all_current.clear();
        current.clear();
        max_score = -INT_MAX;
        int bestx = 0, besty = 0;
        vector<vector<int>> promet = figure;
        int64_t nowr;
        nowr = AlphaBeta(2, depth_, -INT_MAX, INT_MAX);
        podsazka_need = 1;
        figure = promet;
        int bestx_to = 0, besty_to = 0;
        bestx = besty_h.first.first;
        besty = besty_h.first.second;
        bestx_to = besty_h.second.first;
        besty_to = besty_h.second.second;
        podsazka_need = 1;
        bx = bestx;
        by = besty;
        btx = bestx_to;
        bty = besty_to;
    }
}

void check_ur(int x, int y) {
    if (x >= 870 && x <= 970 && y >= 620 && y <= 660) {
        depth_ = 2;
    }
    if (x >= 870 && x <= 970 && y >= 560 && y <= 600) {
        depth_ = 4;
    }
    if (x >= 870 && x <= 970 && y >= 500 && y <= 540) {
        depth_ = 10;
    }
}

void input() {
    sf::RenderWindow window(sf::VideoMode(1000, 700), "Alphashki");
    sf::Image start;
    start.loadFromFile("D:/праки/play_checkers/Изображение WhatsApp 2025-03-05 в 14.51.17_a3df7543.jpg");
    sf::Texture start_;
    start_.loadFromImage(start);
    sf::Sprite start0_;
    start0_.setTexture(start_);
    start0_.setPosition(50, 20);

    sf::Image shaska1;
    shaska1.loadFromFile("D:/праки/play_checkers/queen.png");
    sf::Texture shaska1_;
    shaska1_.loadFromImage(shaska1);
    sf::Sprite shaska10_;
    shaska10_.setTexture(shaska1_);
    shaska10_.setPosition(90, 60);

    sf::Image shaska2;
    shaska2.loadFromFile("D:/праки/play_checkers/queenw.png");
    sf::Texture shaska2_;
    shaska2_.loadFromImage(shaska2);
    sf::Sprite shaska20_;
    shaska20_.setTexture(shaska2_);
    shaska20_.setPosition(90, 520);

    sf::RectangleShape rectangle(sf::Vector2f(64, 64));
    rectangle.setFillColor(sf::Color(100, 250, 50));
    rectangle.setPosition(91, 63);
    bool check_h = 1;

    setlocale(LC_ALL, "Rus");
    setlocale(LC_ALL, "");
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    
    sf::Font font;
    if (!font.loadFromFile("D:/праки/play_checkers/ofont.ru_Zeitmax.ttf")) {
        std::cout << "error";
    }
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color(230, 0, 0));
    text.setPosition(740, 50);
    text.setString(L"Ходы:");

    int ypos = 70;
    sf::Text text0;
    text0.setFont(font);
    text0.setCharacterSize(20);
    text0.setFillColor(sf::Color(240, 240, 240));

    sf::Image start1;
    start1.loadFromFile("D:/файлы программирование/png-klev-club-pmxl-p-pryamougolnaya-knopka-png-25.png");
    sf::Texture start1_;
    start1_.loadFromImage(start1);
    sf::Sprite start10_;
    start10_.setTexture(start1_);
    start10_.setPosition(494, 620);
    start10_.scale(sf::Vector2f(0.2 / 5, 0.2 / 5));

    sf::Image start2;
    start2.loadFromFile("D:/файлы программирование/png-klev-club-pmxl-p-pryamougolnaya-knopka-png-25.png");
    sf::Texture start2_;
    start2_.loadFromImage(start2);
    sf::Sprite start20_;
    start20_.setTexture(start2_);
    start20_.setPosition(60, 620);
    start20_.scale(sf::Vector2f(0.2/5, 0.2/5));

    sf::Image startstr;
    startstr.loadFromFile("D:/праки/play_checkers/free-icon-arrow-down-4655001.png");
    sf::Texture startstr_;
    startstr_.loadFromImage(startstr);
    sf::Sprite startstr0_;
    startstr0_.setTexture(startstr_);
    startstr0_.setPosition(110, 634);
    startstr0_.scale(sf::Vector2f(0.2 / 4, 0.2 / 4));

    sf::Image startzag;
    startzag.loadFromFile("D:/праки/play_checkers/free-icon-downloads-4239049.png");
    sf::Texture startzag_;
    startzag_.loadFromImage(startzag);
    sf::Sprite startzag0_;
    startzag0_.setTexture(startzag_);
    startzag0_.setPosition(546, 634);
    startzag0_.scale(sf::Vector2f(0.2 / 4, 0.2 / 4));

    sf::Image startskach;
    startskach.loadFromFile("D:/файлы программирование/png-klev-club-pmxl-p-pryamougolnaya-knopka-png-25.png");
    sf::Texture startskach_;
    startskach_.loadFromImage(startskach);
    sf::Sprite startskach0_;
    startskach0_.setTexture(startskach_);
    startskach0_.setPosition(346, 620);
    startskach0_.scale(sf::Vector2f(0.2 / 5, 0.2 / 5));

    sf::Image pod_ic;
    pod_ic.loadFromFile("D:/праки/play_checkers/free-icon-tips-5754389.png");
    sf::Texture pod_ic_;
    pod_ic_.loadFromImage(pod_ic);
    sf::Sprite pod_ic0_;
    pod_ic0_.setTexture(pod_ic_);
    pod_ic0_.setPosition(252, 634);
    pod_ic0_.scale(sf::Vector2f(0.2 / 4, 0.2 / 4));

    sf::Image podsk;
    podsk.loadFromFile("D:/файлы программирование/png-klev-club-pmxl-p-pryamougolnaya-knopka-png-25.png");
    sf::Texture podsk_;
    podsk_.loadFromImage(podsk);
    sf::Sprite podsk0_;
    podsk0_.setTexture(podsk_);
    podsk0_.setPosition(200, 620);
    podsk0_.scale(sf::Vector2f(0.2 / 5, 0.2 / 5));

    sf::Image sk_ic;
    sk_ic.loadFromFile("D:/праки/play_checkers/icon_v.png");
    sf::Texture sk_ic_;
    sk_ic_.loadFromImage(sk_ic);
    sf::Sprite sk_ic0_;
    sk_ic0_.setTexture(sk_ic_);
    sk_ic0_.setPosition(400, 634);
    sk_ic0_.scale(sf::Vector2f(0.2 / 4, 0.2 / 4));

    sf::Image ur1;
    ur1.loadFromFile("D:/файлы программирование/png-klev-club-pmxl-p-pryamougolnaya-knopka-png-25.png");
    sf::Texture ur1_;
    ur1_.loadFromImage(ur1);
    sf::Sprite ur10_;
    ur10_.setTexture(ur1_);
    ur10_.setPosition(870, 620);
    ur10_.scale(sf::Vector2f(0.2 / 5, 0.2 / 5));

    sf::Image ur2;
    ur2.loadFromFile("D:/файлы программирование/png-klev-club-pmxl-p-pryamougolnaya-knopka-png-25.png");
    sf::Texture ur2_;
    ur2_.loadFromImage(ur2);
    sf::Sprite ur20_;
    ur20_.setTexture(ur2_);
    ur20_.setPosition(870, 560);
    ur20_.scale(sf::Vector2f(0.2 / 5, 0.2 / 5));

    sf::Image ur3;
    ur3.loadFromFile("D:/файлы программирование/png-klev-club-pmxl-p-pryamougolnaya-knopka-png-25.png");
    sf::Texture ur3_;
    ur3_.loadFromImage(ur3);
    sf::Sprite ur30_;
    ur30_.setTexture(ur3_);
    ur30_.setPosition(870, 500);
    ur30_.scale(sf::Vector2f(0.2 / 5, 0.2 / 5));

    sf::Text tur1;
    tur1.setFont(font);
    tur1.setCharacterSize(12);
    tur1.setFillColor(sf::Color(0, 0, 0));
    tur1.setPosition(914, 640);
    tur1.setString(L"легко");

    sf::Text tur2;
    tur2.setFont(font);
    tur2.setCharacterSize(12);
    tur2.setFillColor(sf::Color(0, 0, 0));
    tur2.setPosition(904, 580);
    tur2.setString(L"умеренно");

    sf::Text tur3;
    tur3.setFont(font);
    tur3.setCharacterSize(12);
    tur3.setFillColor(sf::Color(0, 0, 0));
    tur3.setPosition(912, 520);
    tur3.setString(L"тяжело");

    string alp[] = { "a", "b","c", "d", "e", "f", "g", "h"};

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                window.close();
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2i position = sf::Mouse::getPosition(window);
                int x_ = position.x, y_ = position.y;
                int bul_hod_nazad = 0;
                check_ur(x_, y_);
                if (regim_play == 0) {
                    check_podsk(x_, y_);
                    if (y_ < 600 && x_ < 870) {
                        if (check_h) {
                            podsazka_need = 0;
                            int x = ((x_ - 90) / 65 + 1);
                            int y = 9 - ((y_ - 63) / 65 + 1);
                            xnow = x;
                            ynow = y;
                            check_choose(x, y);
                            check_h = 0;
                        }
                        else {
                            podsazka_need = 0;
                            int x = ((x_ - 90) / 65 + 1);
                            int y = 9 - ((y_ - 63) / 65 + 1);
                            int fl = 0;
                            for (int i = 0; i < all.size(); ++i) {
                                if (all[i].first == x && all[i].second == y) {
                                    fl = 1;
                                }
                            }
                            if (fl == 1) {
                                go_to(x, y);
                                all_hod.push_back({ {xnow, ynow}, {x,y} });
                                figure_pred.push_back(figure);
                                window.draw(start0_);
                                window.draw(text);
                                ypos = 70;
                                for (int i = 0; i < all_hod.size(); ++i) {
                                    if (i % 17 != 0) {
                                        ypos += 30;
                                    }
                                    else {
                                        ypos = 70;
                                        window.clear();
                                        window.draw(start20_);
                                        window.draw(start10_);
                                        window.draw(start0_);
                                        window.draw(text);
                                        window.draw(startzag0_);
                                        window.draw(startstr0_);
                                        window.draw(startskach0_);
                                        window.draw(sk_ic0_);
                                        if (regim_play == 0) {
                                            window.draw(podsk0_);
                                            window.draw(pod_ic0_);
                                           
                                        }
                                        window.draw(ur10_);
                                        window.draw(ur20_);
                                        window.draw(ur30_);
                                        window.draw(tur1);
                                        window.draw(tur2);
                                        window.draw(tur3);
                                    }
                                    text0.setPosition(730, ypos);
                                    string s;
                                    if (i % 2 == 1) {
                                        s += 'b';
                                    }
                                    else {
                                        s += 'w';
                                    }
                                    s += ": ";
                                    s += alp[all_hod[i].first.first - 1];
                                    s += to_string(all_hod[i].first.second);
                                    s += "->";
                                    s += alp[all_hod[i].second.first - 1];
                                    s += to_string(all_hod[i].second.second);
                                    text0.setString(s);
                                    window.draw(text0);
                                }
                                window.draw(start0_);
                                for (int i = 1; i <= 8; ++i) {
                                    for (int j = 1; j <= 8; ++j) {
                                        if (figure[i][j] == 1) {
                                            shaska10_.setPosition(90 + (j - 1) * 65, 60 + (8 - i) * 65);
                                            window.draw(shaska10_);
                                        }
                                        else {
                                            if (figure[i][j] == 2) {
                                                shaska20_.setPosition(90 + (j - 1) * 65, 60 + (8 - i) * 65);
                                                window.draw(shaska20_);
                                            }
                                        }
                                    }
                                }
                                window.display();
                                Sleep(500);
                                all.clear();
                                if (hod % 2 == 1) {
                                    all_generations(1);
                                    hod += 1;
                                }
                                check_h = 1;
                            }
                            else {
                                hod -= 1;
                                all.clear();
                                int x = ((x_ - 90) / 65 + 1);
                                int y = 9 - ((y_ - 63) / 65 + 1);
                                xnow = x;
                                ynow = y;
                                check_choose(x, y);
                                check_h = 0;
                            }
                        }
                    }
                    if (hod_nazad(x_, y_)) {
                        check_h = 1;
                    }
                   
                }
                check_zapis(x_, y_);
                check_skach(x_, y_);
            }
        }
        if (regim_play == 1) {
            if (for_robot != 1000) {
                hod = for_robot;
                for_robot = 1000;
            }
            if (hod % 2 == 1) {
                all_generations(1);
                hod += 1;
            }
            else {
                all_generations(2);
                hod += 1;
            }
            ypos = 70;
            for (int i = 0; i < all_hod.size(); ++i) {
                if (i % 17 != 0) {
                    ypos += 30;
                }
                else {
                    ypos = 70;
                    window.clear();
                    window.draw(start20_);
                    window.draw(start10_);
                    window.draw(start0_);
                    window.draw(text);
                    window.draw(startstr0_);
                    window.draw(startzag0_);
                    window.draw(startskach0_);
                    window.draw(sk_ic0_);
                    if (regim_play == 0) {
                        window.draw(podsk0_);
                        window.draw(pod_ic0_);
                        window.draw(ur10_);
                        window.draw(ur20_);
                        window.draw(ur30_);
                        window.draw(tur1);
                        window.draw(tur2);
                        window.draw(tur3);
                    }
                    window.draw(ur10_);
                    window.draw(ur20_);
                    window.draw(ur30_);
                    window.draw(tur1);
                    window.draw(tur2);
                    window.draw(tur3);
                }
                text0.setPosition(730, ypos);
                string s;
                if (i % 2 == 1) {
                    s += 'b';
                }
                else {
                    s += 'w';
                }
                s += ": ";
                s += alp[all_hod[i].first.first - 1];
                s += to_string(all_hod[i].first.second);
                s += "->";
                s += alp[all_hod[i].second.first - 1];
                s += to_string(all_hod[i].second.second);
                text0.setString(s);
                window.draw(text0);
            }
            for (int i = 1; i <= 8; ++i) {
                for (int j = 1; j <= 8; ++j) {
                    if (figure[i][j] == 1) {
                        shaska10_.setPosition(90 + (j - 1) * 65, 60 + (8 - i) * 65);
                        window.draw(shaska10_);
                    }
                    else {
                        if (figure[i][j] == 2) {
                            shaska20_.setPosition(90 + (j - 1) * 65, 60 + (8 - i) * 65);
                            window.draw(shaska20_);
                        }
                    }
                }
            }
            window.display();
            Sleep(2000);
            
        }
        ypos = 70;
        for (int i = 0; i < all_hod.size(); ++i) {
            if (i % 17 != 0) {
                ypos += 30;
            }
            else {
                ypos = 70;
                window.clear();
                window.draw(start20_);
                window.draw(start10_);
                window.draw(start0_);
                window.draw(text);
                window.draw(startstr0_);
                window.draw(startzag0_);
                window.draw(startskach0_);
                window.draw(sk_ic0_);
                if (regim_play == 0) {
                    window.draw(podsk0_);
                    window.draw(pod_ic0_);
                    window.draw(ur10_);
                    window.draw(ur20_);
                    window.draw(ur30_);
                    window.draw(tur1);
                    window.draw(tur2);
                    window.draw(tur3);
                }
                window.draw(ur10_);
                window.draw(ur20_);
                window.draw(ur30_);
                window.draw(tur1);
                window.draw(tur2);
                window.draw(tur3);
            }
            text0.setPosition(730, ypos);
            string s;
            if (i % 2 == 1) {
                s += 'b';
            }
            else {
                s += 'w';
            }
            s += ": ";
            s += alp[all_hod[i].first.first - 1];
            s += to_string(all_hod[i].first.second);
            s += "->";
            s += alp[all_hod[i].second.first - 1];
            s += to_string(all_hod[i].second.second);
            text0.setString(s);
            window.draw(text0);
        }
        window.draw(start0_);
        window.draw(text);
        for (int i = 1; i <= 8; ++i) {
            for (int j = 1; j <= 8; ++j) {
                if (figure[i][j] == 1) {
                    shaska10_.setPosition(90 + (j-1) * 65, 60 + (8-i)*65);
                    window.draw(shaska10_);
                }
                else {
                    if (figure[i][j] == 2) {
                        shaska20_.setPosition(90 + (j - 1) * 65, 60 + (8-i) * 65);
                        window.draw(shaska20_);
                    }
                }
            }
       }   
        if (podsazka_need) {
            sf::RectangleShape ramka(sf::Vector2f(65, 65));
            ramka.setPosition((bx - 1) * 65 + 91, (8 - by) * 65 + 63);
            ramka.setFillColor(sf::Color::Transparent);
            ramka.setOutlineThickness(3);
            ramka.setOutlineColor(sf::Color(0, 250, 0));
            window.draw(ramka);
            sf::RectangleShape ramka1(sf::Vector2f(65, 65));
            ramka1.setPosition((btx - 1) * 65 + 91, (8 - bty) * 65 + 63);
            ramka1.setFillColor(sf::Color::Transparent);
            ramka1.setOutlineThickness(3);
            ramka1.setOutlineColor(sf::Color(0, 250, 0));
            window.draw(ramka1);
        }

        for (int k = 0; k < all.size(); ++k) {
            sf::RectangleShape ramka(sf::Vector2f(65, 65));
            ramka.setPosition((all[k].first-1) * 65 + 91, (8 - all[k].second) * 65 + 63);
            ramka.setFillColor(sf::Color::Transparent);
            ramka.setOutlineThickness(3);
            ramka.setOutlineColor(sf::Color(250, 0, 0));
            window.draw(ramka);
        }
        window.draw(start20_);
        window.draw(start10_);
        window.draw(startstr0_);
        window.draw(text);
        window.draw(startzag0_);
        window.draw(startskach0_);
        window.draw(sk_ic0_);
        if (regim_play == 0) {
            window.draw(podsk0_);
            window.draw(pod_ic0_);
            window.draw(ur10_);
            window.draw(ur20_);
            window.draw(ur30_);
            window.draw(tur1);
            window.draw(tur2);
            window.draw(tur3);
        }
        window.draw(ur10_);
        window.draw(ur20_);
        window.draw(ur30_);
        window.draw(tur1);
        window.draw(tur2);
        window.draw(tur3);
        window.display();
        window.clear();
        if (endi == 1) {
            return;
        }
    }
}
int main() {
    isx();
    if (regim_play) {
        for_robot = rand() % 2;
    }
    zapoln();
    raskr();
    figure_pred.push_back(figure);
    input();
}