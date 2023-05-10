#include "include\ListArr.hpp"

#include <iostream>
#include <chrono>
#include <cmath>
#include <random>
#include <algorithm>

#include <vector>
#include <list>

using std::cout;

//? Para compilar y ejecutar el programa:
//? "g++ mainExperimental.cpp source/*.cpp -o mainExperimental && ./mainExperimental"

const int INITIAL_ELEMENTS = 10;

const int ITERATIONS = 5;
const int NUM_ITERATIONS = 20;

void insert_left_comparison(const int listArr_size) {
    cout << "* Comparaciones de insert_left() con " << listArr_size << " elementos en arreglos de ListArr:" << '\n';

    for (int i = 0; i < ITERATIONS; i++) {
        int n = INITIAL_ELEMENTS * pow(10, i);

        double avg_list_arr = 0, avg_vector = 0, avg_list = 0;
        // Repetición del experimento
        for (int j = 0; j < NUM_ITERATIONS; j++) {
            ListArr my_list_arr(listArr_size);
            std::vector<int> my_vector;
            std::list<int> my_list;

            // * ListArr
            auto start = std::chrono::high_resolution_clock::now();
            for (int k = 0; k < n; k++) {
                my_list_arr.insert_left(rand() % n);
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            avg_list_arr += duration.count();

            // * Vector
            start = std::chrono::high_resolution_clock::now();
            for (int k = 0; k < n; k++) {
                my_vector.insert(my_vector.begin(), rand() % n);
            }
            end = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            avg_vector += duration.count();

            // * List
            start = std::chrono::high_resolution_clock::now();
            for (int k = 0; k < n; k++) {
                my_list.push_front(rand() % n);
            }
            end = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            avg_list += duration.count();
        }

        avg_list_arr /= NUM_ITERATIONS;
        avg_vector /= NUM_ITERATIONS;
        avg_list /= NUM_ITERATIONS;

        cout << "Promedios de " << NUM_ITERATIONS << " tests de " << n << " elementos:" << '\n';
        cout << " ListArr: " << (int)avg_list_arr << " us, ";
        cout << "Vector: " << (int)avg_vector << " us, ";
        cout << "List: " << (int)avg_list << " us" << '\n';
    }
    cout << '\n';
}


void insert_right_comparison(const int listArr_size) {
    cout << "* Comparaciones de insert_right() con " << listArr_size << " elementos en arreglos de ListArr:" << '\n';

    for (int i = 0; i < ITERATIONS; i++) {
        int n = INITIAL_ELEMENTS * pow(10, i);

        double avg_list_arr = 0, avg_vector = 0, avg_list = 0;
        // Repetición del experimento
        for (int j = 0; j < NUM_ITERATIONS; j++) {
            ListArr my_list_arr(listArr_size);
            std::vector<int> my_vector;
            std::list<int> my_list;

            // * ListArr
            auto start = std::chrono::high_resolution_clock::now();
            for (int k = 0; k < n; k++) {
                my_list_arr.insert_right(rand() % n);
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            avg_list_arr += duration.count();

            // * Vector
            start = std::chrono::high_resolution_clock::now();
            for (int k = 0; k < n; k++) {
                my_vector.push_back(rand() % n);
            }
            end = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            avg_vector += duration.count();

            // * List
            start = std::chrono::high_resolution_clock::now();
            for (int k = 0; k < n; k++) {
                my_list.push_back(rand() % n);
            }
            end = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            avg_list += duration.count();
        }

        avg_list_arr /= NUM_ITERATIONS;
        avg_vector /= NUM_ITERATIONS;
        avg_list /= NUM_ITERATIONS;

        cout << "Promedios de " << NUM_ITERATIONS << " tests de " << n << " elementos:" << '\n';
        cout << " ListArr: " << (int)avg_list_arr << " us, ";
        cout << "Vector: " << (int)avg_vector << " us, ";
        cout << "List: " << (int)avg_list << " us" << '\n';
    }
    cout << '\n';
}

void find_comparison(const int listArr_size) {
    cout << "* Comparaciones de find_comparison() con " << listArr_size << " elementos en arreglos de ListArr:" << '\n';
    int nFindTest = NUM_ITERATIONS * 5;

    for (int i = 0; i < ITERATIONS; i++) {
        int n = INITIAL_ELEMENTS * pow(10, i);

        int avg_list_arr = 0, avg_vector = 0, avg_list = 0;
        bool found_list_arr, found_vector, found_list;
        // Repetición del experimento
        for (int j = 0; j < NUM_ITERATIONS; j++) {
            ListArr my_list_arr(listArr_size);
            std::vector<int> my_vector;
            std::list<int> my_list;

            // Llenamos las estructuras con elementos aleatorios
            for (int i = 0; i < n - 1; i++) {
                int num = rand() % n;
                my_list_arr.insert_right(num);
                my_vector.push_back(num);
                my_list.push_back(num);
            }

            // Definimos el elemento a buscar y lo insertamos en posición aleatoria
            int num = rand() % n, pos = rand() % n;
            my_list_arr.insert(num, pos);
            my_vector.insert(my_vector.begin() + pos, num);
            auto it = my_list.begin();
            std::advance(it, pos);
            my_list.insert(it, num);

            // * ListArr
            auto start = std::chrono::high_resolution_clock::now();

            found_list_arr = my_list_arr.find(num);

            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            avg_list_arr += duration.count();

            // * Vector
            start = std::chrono::high_resolution_clock::now();

            // found_vector = (std::find(my_vector.begin(), my_vector.end(), num) != my_vector.end());
            for (auto i : my_vector) {
                if (i == num) {
                    found_vector = true;
                    break;
                }
            }

            end = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            avg_vector += duration.count();

            // * List
            start = std::chrono::high_resolution_clock::now();

            // found_list = (std::find(my_list.begin(), my_list.end(), num) != my_list.end());
            for (auto i : my_list) {
                if (i == num) {
                    found_list = true;
                    break;
                }
            }

            end = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            avg_list += duration.count();

            // Verificamos que los resultados sean los mismos
            if (found_list_arr != found_vector || found_list_arr != found_list) {
                cout << "Error en la búsqueda." << '\n';
                return;
            }
        }

        avg_list_arr /= NUM_ITERATIONS;
        avg_vector /= NUM_ITERATIONS;
        avg_list /= NUM_ITERATIONS;

        cout << "Promedios de " << NUM_ITERATIONS << " tests de " << n << " elementos:" << '\n';
        cout << " ListArr: " << (int)avg_list_arr << " us, ";
        cout << "Vector: " << (int)avg_vector << " us, ";
        cout << "List: " << (int)avg_list << " us" << '\n';
    }
    cout << '\n';
}

int main() {
    srand(time(nullptr));

    int sizes[] = {1, 64, 128, 512, 1024};

    for (int i = 0; i < 5; i++) {
        // * Comparación de insert_left()
        insert_left_comparison(sizes[i]);

        // * Comparación de insert_right()
        insert_right_comparison(sizes[i]);

        // * Comparación de find()
        find_comparison(sizes[i]);
    }

    return 0;
}