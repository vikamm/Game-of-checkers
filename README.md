# Game-of-checkers
Реализация новой игры альпашки с ипользованием алгоритма alpha-beta отсечения

# Правила игры: 

Игра похожа на обычные русские шашки с некоторыми модификациями:
1) Победа присуждается игроку, который первым достигнул самую дальнюю горизонталь поля противника.
2) Фигура  может совершать ходы, как в обычных шашках, однако обязана "есть" назад.
# Вид игры (front):
![alt text](https://github.com/vikamm/Game-of-checkers/blob/main/photo_front.png)
1) Игра поддерживает три уровня сложности (от выбора уровня зависит глубина рекурсии, как следствие количество конфигураций наперед просматриваемых "роботом")
2) Существует кнопка подсказки, при нажатии которой отображается наиболее благоприятный в данной ситуации ход.
3) Есть возможности выгрузки текущей конфигурации игры в файл и загрузки любой существующей конфигурации из файла.
4) Есть возможность перейти к предыдущему ходу пользователя.
5) Сбоку отоображается последовательность ходов робота и пользователя.
