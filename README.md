# Ultimate Tic Tac Toe

## Правила
[Правила из википедии](https://en.wikipedia.org/wiki/Ultimate_tic-tac-toe#Rules)

Первый / второй игрок - крестик / нолик.

Действия игры происходят на поле размером 9 на 9 клеток. Поле разбивается на 9 блоков (далее - **блок**) размером 3 на 3 каждый.

Первый ходит в любую клетку.

далее ходят второй и первый по очереди:

1. определить, в какую клетку в **блоке** попал предыдущий игрок (0 - 8),

2. сделать ход в **блоке** с тем же индексом, что и ячейка **блока** предыдущего игрока, если данный **блок** не *помечен*.
    - если же данный **блок** *помечен*, текущий игрок будет должен походить в любую клетку в любом *непомеченном* **блоке**.

Если в каком-либо **блоке** происходит победа первого,вторго игрока, или ничья, он *помечается* как победный для первого, втоорого игрока, или ничейный.

Побеждает тот, кто первым достигнет состояния поля, при котором из **блоков** будет видно, кто победил по обычным правилам игры в крестики-нолики.

## Движок игры

### Трансформации поля

трансформации поля нужны для ускорения поиска ходов, ведь нету разницы между ходом в левый верхний угол и ходом в правыйнижний например.

каждую из восьми трансформаций (поворот и отражения) можно описать с помощью матриц! 

удобно для создания аглгоритма поиска индекса рассортировать матрицы так, как показано ниже:

индекс | матрица | описание трансформации
-|-|-
000 | $$\begin{bmatrix} 1& 0 \\\  0& 1\end{bmatrix}$$ | без изменений
001 | $$\begin{bmatrix}-1& 0 \\\  0& 1\end{bmatrix}$$ | отражение по вертикали
010 | $$\begin{bmatrix} 1& 0 \\\  0&-1\end{bmatrix}$$ | отражение по горизонтали
011 | $$\begin{bmatrix}-1& 0 \\\  0&-1\end{bmatrix}$$ | поворот на $$180\degree$$
100 | $$\begin{bmatrix} 0& 1 \\\  1& 0\end{bmatrix}$$ | отражение относительно прямой $$y=x$$
101 | $$\begin{bmatrix} 0&-1 \\\  1& 0\end{bmatrix}$$ | поворот против часовой стрелки на $$90\degree$$
110 | $$\begin{bmatrix} 0& 1 \\\ -1& 0\end{bmatrix}$$ | поворот по часовой стрелке на $$90\degree$$
111 | $$\begin{bmatrix} 0&-1 \\\ -1& 0\end{bmatrix}$$ | отражение относительно прямой $$y=-x$$

здесь третий бит отвечает за расположение единиц по побочной / главной диагонали

второй бит за знак последних двух элементов матрицы ( - / + )

первый бит за знак первых двух элементов матрицы ( - / + )