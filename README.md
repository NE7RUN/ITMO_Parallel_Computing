# Параллельное программирование

ITMO University "Parallel Computing" course. 1st year, 2nd semester

# Лабораторная №1: Автоматическое распараллеливание программ #
**Вариант A = 576; map= 6|5; merge=1; sort=6**

1. На компьютере с многоядерным процессором установить ОС Linux и компилятор GCC версии не ниже 4.7.2. При невозможности установить Linux или отсутствии компьютера с многоядерным процессором можно выполнять лабораторную работу на виртуальной машине. Минимальное количество ядер при использовании виртуальной машины - 2.

2. На языке Cи написать консольную программу lab1.c, решающую задачу, указанную в п.IV (см. ниже).     
   
   Map - в массиве M1 к каждому элементу применить операцию: кубический корень после деления на e.
        Затем в массиве М2 каждый элемент поочередно сложить с предыдущим, а к рез-ту сложения применить:
        Натуральный логарифм модуля тангенса.  
   
   Merge - в массивах М1 и М2 ко всем элементам с одинаковыми индексами применить операцию: 
        Возведение в степень (т.е. `M2[i] = M1[i]^M2[i]`)  
    
    Sort - отсортировать полученный массив методом сортировки вставками  
    
    Reduce - Рассчитать сумму синусов тех элементов массива
М2, которые при делении на минимальный ненулевой элемент массива М2 дают чётное число (при определении чётности учитывать только целую часть числа). Результатом работы программы по
окончании пятого этапа должно стать одно число X, которое следует использовать для верификации программы после внесения в
неё изменений (например, до и после распараллеливания итоговое
число X не должно измениться в пределах погрешности). Данное
число необходимо выводить на каждой итерации на этапе верификации. Значение числа X следует привести в отчёте для различных
значений N.

  
  
  
В программе нельзя использовать библиотечные функции сортировки, выполнения матричных операций и расчёта статистических величин. В программе нельзя использовать библиотечные функции, отсутствующие в стандарт- ных заголовочных файлах stdio.h, stdlib.h, math.h, sys/time.h. Задача должна решаться 100 раз с разными начальными значениями ге- нератора случайных чисел (ГСЧ). Структура программы примерно следующая:
```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
int main(int argc, char* argv[])
{
    int i, N;
    struct timeval T1, T2;
    long delta_ms;
    N = atoi(argv[1]); /* N равен первому параметру командной строки */
    gettimeofday(&T1, NULL); /* запомнить текущее время T1 */
    for (i=0; i<100; i++) /* 100 экспериментов */
    {
        /* инициализировать начальное значение ГСЧ   */
        /* Заполнить массив исходных данных размером N */
        /* Решить поставленную задачу, заполнить массив с результатами
        /* Отсортировать массив с результатами указанным методом */
    }
    gettimeofday(&T2, NULL);   /* запомнить текущее время T2 */
    delta_ms =  1000*(T2.tv_sec - T1.tv_sec) + (T2.tv_usec - T1.tv_usec) / 1000;
    printf("\nN=%d. Milliseconds passed: %ld\n", N, delta_ms); /* T2 - T1 */
    return 0;
}
```

3. Скомпилировать написанную программу без использования авто- матического распараллеливания с помощью следующей команды: `/home/user/gcc -O3 -Wall -Werror -o lab1-seq lab1.c`

4. Скомпилировать написанную программу, используя встроенное в gcc средство автоматического распараллеливания Graphite с помо- щью следующей команды `/home/user/gcc -O3 -Wall -Werror -floop- parallelize-all -ftree-parallelize-loops=K lab1.c -o lab1-par-K` (пере- менной K поочерёдно присвоить хотя бы 4 значения: 1, меньше количества ядер, равное количеству физических ядер и больше ко- личества физических ядер).

5. В результате получится одна нераспараллеленная программа и че- тыре или более распараллеленных.

6. Закрыть все работающие в операционной системе прикладные про- граммы (включая Winamp, uTorrent, браузеры и Skype), чтобы они не влияли на результаты последующих экспериментов. При ис- пользовании ноутбука необходимо иметь постоянное подключение к сети питания, на время проведения эксперимента.

7. Запускать файл lab1-seq из командной строки, увеличивая значения N до значения N1, при котором время выполнения превысит 0.01 с. Подобным образом найти значение N=N2, при котором время выполнения превысит 5 с.

8. Используя найденные значения N1 и N2, выполнить следующие эксперименты (для автоматизации проведения экспериментов рекомендуется написать скрипт):
    - запускать lab1-seq для значений `N = N1, N1+∆, N1+2∆, N1+3∆,..., N2` и записывать получающиеся значения времени `delta_ms(N)` в функцию `seq(N)`;
    - запускать lab1-par-K для значений `N = N1, N1+∆, N1+2∆, N1+3∆,..., N2` и записывать получающиеся значения времени `delta_ms(N)` в функцию `par − K(N)`;
    - значение ∆ выбрать так: `∆ = (N2 − N1)/10`.

9. Провести верификацию значения X. Добавить в конец цикла вывод значения X и изменить количество экспериментов на 5. Сравнить значения X для распараллеленной программы и не распараллеленной.

10. Написать отчёт о проделанной работе.

11. Подготовиться к устным вопросам на защите.

12. Найти вычислительную сложность алгоритма до и после распарал- леливания, сравнить полученные результаты.

13. Необязательное задание No1 (для получения оценки «четыре» и «пять»). Провести аналогичные описанным экс- перименты, используя вместо gcc компилятор Solaris Studio (или любой другой на своё усмотрение). При компиля- ции следует использовать следующие опции для автома- тического распараллеливания: `solarisstudio -cc -O3 - xautopar -xloopinfo lab1.c`.

14. Необязательное задание No2 (для получения оценки «пять»). Это задание выполняется только после выполнения предыдущего пункта. Провести аналогичные описанным эксперименты, исполь- зуя вместо gcc компилятор Intel ICC (или любой другой на своё усмотрение). В ICC следует при компиляции использовать следу- ющие опции для автоматического распараллеливания: `icc -parallel -par-threashold0 -par-num-threads=K -o lab1-icc-par-K lab1.c`.



# Лабораторная №2: Исследование эффективности параллельных библиотек для C-программ #

1. В исходном коде программы, полученной в результате выполнения лабораторной работы №1, нужно на этапах Map и Merge все циклы
с вызовами математических функций заменить их векторными ана- логами из библиотеки «AMD Framewave» (http://framewave. sourceforge.net). При выборе конкретной Framewave-функции необходимо убедиться, что она помечена как `MT` (Multi-Threaded), т.е. распараллеленная. Полный перечень доступных функций на- ходится по ссылке: http://framewave.sourceforge.net/Manual/fw_section_060.html#fw_section_060. Например, Framewave-функция `min` в списке поддерживаемых технологий имеет только `SSE2`, но не `MT`.

    ***Примечание:*** выбор библиотеки Framewave не является обязатель- ным, можно использовать любую другую параллельную библиоте- ку, если в ней нужные функции распараллелены, так, например, можно использовать ATLAS (для этой библиотеки необходимо вы- ключить троттлинг и энергосбережение, а также разобраться с ме- ханизмом изменения числа потоков) или Intel Integrated Performance Primitives.

2. Добавить в начало программы вызов Framewave-функции `SetNumThreads(M)` для установки количества создаваемых парал- лельной библиотекой потоков, задействуемых при выполнении рас- параллеленных Framewave-функций. Нужное число M следует уста- навливать из параметра командной строки `(argv)` для удобства ав- томатизации экспериментов.

    ***Примечание:*** При использовании Intel IPP функцию SetNumThreads(M) не нужно использовать. Необходимо компилировать программу под разное количество потоков.

3. Скомпилировать программу, не применяя опции автоматического распараллеливания, использованные в лабораторной работе №1. Провести эксперименты с полученной программой для тех же значений N1 и N2, которые использовались в лабораторной работе No1, при M = 1, 2, . . . , K, где K – количество процессоров (ядер) на экспериментальном стенде.

4. Сравнить полученные результаты с результатами лабораторной ра- боты No1: на графиках показать, как изменилось время выполне- ния программы, параллельное ускорение и параллельная эффективность.

5. Написать отчёт о проделанной работе.

6. Подготовиться к устным вопросам на защите.

7. **Необязательное задание №1** (для получения оценки «четыре» и «пять»). Исследовать параллельное ускорение для различных зна- чений M > K, т.е. оценить накладные расходы при создании чрез- мерного большого количества потоков. Для иллюстрации того, что программа действительно распараллелилась, привести график за- грузки процессора (ядер) во время выполнения программы при N = N2 для всех использованных M. Для получения графика можно как написать скрипт, так и просто сделать скриншот дис- петчера задач, указав на скриншоте моменты начала и окончания эксперимента (в отчёте нужно привести текст скрипта или назва- ние использованного диспетчера).

8. **Необязательное задание №2** (для получения оценки «пять»). Это задание выполняется только после выполнения предыдущего пунк- та. Используя закон Амдала, рассчитать коэффициент распаралле- ливания для всех экспериментов и привести его на графиках. Про- комментировать полученные результаты.


# Лабораторная №3: Распараллеливание циклов с помощью технологии OpenMP


1. Добавить во все for-циклы (кроме цикла в функции main, указывающего количество экспериментов)
в программе из ЛР №1 следующую директиву OpenMP:
```#pragma omp parallel for default(none) private(...) shared(...)```
Наличие параметра default(none) является обязательным.

2. Проверить все for-циклы на внутренние зависимости по данным
между итерациями. Если зависимости обнаружились, использовать
для защиты критических секций директиву ”#pragma omp critical”
или ”#pragma omp atomic” (если операция атомарна), или параметр
reduction (предпочтительнее) или вообще отказаться от распарал-
леливания цикла (свой выбор необходимо обосновать).

3. Убедиться, что получившаяся программа обладает свойством прямой
совместимости с компиляторами, не поддерживающими OpenMP
(для проверки этого можно скомпилировать программу без опции `–fopenmp`,
в результате не должно быть сообщений об
ошибках, а программа должна корректно работать).

4. Использовать функцию SetNumThreads для изменения числа потоков.
В отчете указать максимальное количество потоков.

5. Провести эксперименты, замеряя параллельное ускорение.
Привести сравнение графиков параллельного ускорения с ЛР №1 и ЛР №2.

6. Провести эксперименты, добавив параметр ”schedule” и варьируя
в экспериментах тип расписания. Исследование нужно провести
для всех возможных расписаний: static, dynamic, guided.
С 4 вариантами chunck_size равными: единице, меньше чем число
потоков, равному числу потоков и больше чем число потоков. Привести
сравнение параллельного ускорения при различных расписаниях с
результатами п.4.

7. Определить какой тип расписания на машине при использовании
`schedule` `default`.

8. Выбрать из рассмотренных в п.4 и п.5 наилучший вариант при
различных N. Сформулировать условия, при которых наилучшие
результаты получились бы при использовании других типов рас-
писания.

9. Найти вычислительную сложность алгоритма до и после распарал-
леливания, сравнить полученные результаты.

10. Для иллюстрации того, что программа действительно распаралле-
лилась, привести график загрузки процессора (ядер) от времени
при выполнении программы при N
= N1 для лучшего варианта
распараллеливания. Для получения графика можно как написать
скрипт так и просто сделать скриншот диспетчера задач, указав
на скриншоте моменты начала и окончания эксперимента (в от-
чёте нужно привести текст скрипта или название использованно-
го диспетчера). Недостаточно привести однократное моментальное
измерение загрузки утилитой htop, т.к. требуется привести график
изменения загрузки за всё время выполнения программы.

11. Написать отчёт о проделанной работе.

12. Подготовиться к устным вопросам на защите.

13. **Необязательное задание №1**
(для получения оценки «четыре» и «пять»).
Построить график параллельного ускорения для точек N < N1
и найти значения N, при которых накладные расходы
на распараллеливание превышают выигрыш от распараллеливания
(независимо для различных типов расписания).

14. **Необязательное задание №2** (для получения оценки «пять»)
Для лучшего результата по итогам всех экспериментов сделать еще
минимум 3 эксперимента, заменив флаг -O3 на другие флаги оптимизации.
Построить график времени выполнения от N.
