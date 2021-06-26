# Сортировка файла, размером 1e7 и 1e8 случайных двухбайтовых чисел

При запуске генерирует файл ./numbers.bin, размером 1e7 или 1e8 (только для теста RadixSortE8) случайных двухбайтовых чисел (если его нет), и сортирует заданным способом.
Для запуска очередного теста необходимо удалить отсортированный файл и временный файл, командой: 
```shell
rm -f ./numbers.bin ./numbers.bin.tmp
```

# Зависимости сборки

* c++11
* cmake
* gtest

# Сборка cmake

``` shell
mkdir ../build
cd ../build
cmake ..
cmake --build .
```

## Запуск тестов

```shell 
./sort_binary_file --gtest_filter=BinFileSortTest.MergeSort      # merge sort file 1e7
./sort_binary_file --gtest_filter=BinFileSortTest.CombinedSort   # combined sort file 1e7
./sort_binary_file --gtest_filter=BinFileSortTest.RadixSortE7    # radix sort file 1e7
./sort_binary_file --gtest_filter=BinFileSortTest.RadixSortE8    # radix sort file 1e8
```

# Docker

```shell
docker build -t testing .
docker run -it testing sh
/src/testing/build/testing
```
