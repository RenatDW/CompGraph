## 1 часть 
### 1. Загрузка и чтение моделей. (Сделано)
Вместо сырого ObjReader должна быть качественная протестированная реализация: ваша или другого студента, если вы ее не делали в третьей задаче. А также должна быть возможность сохранения модели с помощью ObjWriter по кнопке в меню.

### 2. Сцена. (Сделано)
Сейчас в программе только одна модель. Нужно добавить работу с несколькими. При этом должна остаться возможность перемещать, вращать и как-то изменять (см. работу другого студента) только одну из них. Продумайте, как можно пользователю выбирать, какая/какие (множественный вариант сложнее в реализации, но интереснее) из моделей сейчас активные, т.е выбраны для применения разных трансформаций, сохранения и т.д. В этом пункте очень важен выбор грамотной архитектуры внутри приложения. Можно обсудить её с товарищами.

### 3. Удаление части модели. 
На основе кода других студентов добавьте возможность удалять вершины и полигоны внутри программы. Интерфейс продумайте самостоятельно.

### 4. Интерфейс. 
Эти пункты, а также то, что выполняют другие члены команды, обязывает развивать интерфейс программы. В вашу зону ответственности входит написание его таким, чтобы с ним было удобно работать. А еще хорошо бы продумать стиль приложения: добавить цвета, оформление. При желании можно сделать динамическое переключение тем: например, "светлая/темная".

### 5. Обработка ошибок. 
Пока это касается только ObjReader, но вы можете продумать и другие случаи. Модуль выплёвывает exception’ы, если приходит некорректный файл. Эти исключения пока никак не используются. А нужно выводить окошко с ошибкой, чтобы пользователь мог обдумать свое поведение и щелкнуть “ок”, а не получить зависание или падение программы.

### 6. Деплой. 
Провести финальную работу по деплою приложения. При последней сдаче его следует запускать не из среды разработки, а как самостоятельное портативное приложение.

***

## 2 часть
### 1. Модуль для математики. (Сделано)
В программе в качестве библиотеки для работы с линейной алгеброй используется javax.vecmath. А нужно использовать свой
модуль, либо то, что реализовал ваш однокурсник, если у вас не было такого варианта в третьей задаче. То есть нужно переделать всю работу с математикой на наш собственный пакет Math.

### 2. Вектора-столбцы. (Сделано)
На данный момент во всех матричных преобразованиях в коде предполагается, что мы работаем с векторами-строками. Необходимо переделать методы так, чтобы векторы были столбцами. Помните, что вам придётся транспонировать матрицы и поменять порядок их перемножения.

### 3. Аффинные преобразования. (Сделано) 
В программе реализована только часть графического конвейера. Нет перегонки из локальных координат в мировые координаты сцены. Вам нужно реализовать её, то есть добавить аффинные преобразования: масштабирование, вращение, перенос. Можете использовать наработки студентов из предыдущей задачи. И не забудьте про тесты, без них визуально может быть сложно отследить баги.

### 4. Трансформация модели. (Сделано)
После реализации всего конвейера, нужно добавить в меню настройку модели. Необходима возможность масштабировать ее вдоль
каждой из осей, вокруг каждой из осей поворачивать и перемещать. При сохранении модели (см. работу другого студента) следует выбирать, учитывать трансформации модели или нет. То есть нужна возможность сохранить как исходную модель, так и модель после преобразований. Посоветуйтесь с человеком, отвечающим за интерфейс, он может выделить вам место под нужные кнопки.

### 5. Управление камерой. (Сделано)
Сейчас взаимодействие с камерой не очень удобное, используется только клавиатура. Но можно переделать его, добавив в систему
мышь. За основу можете взять управление из компьютерной игры или приложения для работы с трехмерной графикой. Здесь хорошо бы продумать горячие клавиши и заодно упростить управление моделями.

***

## 3 Часть
### 1.Подготовка к отрисовке. (Сделано)
Добавить возможность триангуляции модели и вычисления её нормалей после загрузки. Можно использовать код однокурсников из третьей задачи. Нормали следует пересчитывать даже если те сохранены в файле, потому что мы не можем им доверять.

### 2.Растеризация полигонов. (Сделано)
Добавить заполнение полигонов одним цветом, используя растеризацию треугольников, написанную студентом во втором задании. Учтите, что вам потребуется алгоритм Z-буффера, чтобы при рендере задние полигоны не вылезали на передние.

### 3.Текстура и освещение. (Сделано) Подумать что делать когда цвет выбран (1-10,1-10,1-10)
Используя уже написанный метод, можно легко дополнить программу наложением текстуры (её как картинку следует подгружать в меню). А после следует реализовать простейшую модель освещения. Источник освещения можно привязывать к текущей камере.Используя сглаживание нормалей, вы сможете мягко опоясывать объекты светом.

### 4.Режимы отрисовки. (Сделано)
Когда все описанные выше пункты будут готовы, надо добавить в программу возможность переключения между режимами. Чтобы легко перебирать все возможные случаи, предлагается оформление в виде галочек (ваши названия могут отличаться):
- Рисовать полигональную сетку
- Использовать текстуру
- Использовать освещение

Так, например, если не выбрана ни одна галочка, модель окрашивается статическим цветом, выбор которого, кстати, можно вынести в меню. В этом режиме для оптимизации можно вызывать не наш метод отрисовки треугольника, а библиотечный. Если добавляется галочка использовать освещение, цвет по модели становится то ярче, то темнее. При добавлении использовать текстуру он подменяется на те значения пикселей, что были на текстуре. А галочка рисовать полигональную сетку нарисует поверх всего контуры полигонов. Тут необязательно, но тоже было бы хорошо добавить Z-буффер (для этого придется вставить самостоятельную растеризацию прямых).

### 5.Несколько камер. (Сделано)
Нужно добавить поддержку нескольких камер в сцене.Задание похоже на добавление нескольких моделей, так что имеет смысл обсудить архитектуру приложения с однокурсниками. Должна быть возможность создавать, удалять камеры, а также переключаться между ними. Сами камеры тоже могут быть видны на сцене в виде трехмерных моделей.
