#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <chrono> 
#include <algorithm>
using namespace std;
using namespace chrono;

void add_all_we_do_to_file(const string& what_we_do,const string& file_name) {
    ofstream file(file_name, ios::app);
    if (file.is_open()) {
        file << what_we_do << endl;
        file.close(); 
    }
    else {
        cout << "Ошибка при открытии файла для записи." << endl;
    }
}
struct red_black_tree {
    int number;
    string color = "black";
    red_black_tree* left = nullptr, * right = nullptr, * parent = nullptr;
};
void print_tree(red_black_tree* tree, int level = 0) {
    if (tree == nullptr) {
        return;
    }
    print_tree(tree->right, level + 1);
    cout << setw(level * 4) << ""; 
    cout <<" --> "<< tree->number << " (" << tree->color << ")" << endl;
    print_tree(tree->left, level + 1);
}
void rotation_to_left(red_black_tree*& tree, red_black_tree*& elem) {
    add_all_we_do_to_file("--> Выполняем вращение влево для узла: " + to_string(elem->number), "output_ans.txt");
    red_black_tree* right_child = elem->right;
    elem->right = right_child->left;
    if (elem->right != nullptr) {
        elem->right->parent = elem;
    }
    right_child->parent = elem->parent;
    if (elem->parent == nullptr) {
        tree = right_child;
    }
    else if (elem == elem->parent->left) {
        elem->parent->left = right_child;
    }
    else {
        elem->parent->right = right_child;
    }
    right_child->left = elem;
    elem->parent = right_child;
}
void rotation_to_right(red_black_tree*& tree, red_black_tree*& elem) {
    add_all_we_do_to_file("--> Выполняем вращение вправо для узла: " + to_string(elem->number), "output_ans.txt");
    red_black_tree* left_child = elem->left;
    elem->left = left_child->right;
    if (elem->left != nullptr) {
        elem->left->parent = elem;
    }
    left_child->parent = elem->parent;
    if (elem->parent == nullptr) {
        tree = left_child;
    }
    else if (elem == elem->parent->right) {
        elem->parent->right = left_child;
    }
    else {
        elem->parent->left = left_child;
    }
    left_child->right = elem;
    elem->parent = left_child;
}

void fix_red_black_tree(red_black_tree*& tree, red_black_tree*& child) {
    add_all_we_do_to_file("--> Проверяем дерево на дисбаланс", "output_ans.txt");
    time_point<steady_clock, duration<__int64, ratio<1, 1000000000>>>start_time, end_time;
    nanoseconds result1;
    start_time = steady_clock::now();
    while (child != tree && child->parent != nullptr && child->parent->color == "red") {
        red_black_tree* par = child->parent;
        red_black_tree* grandpar = par->parent;
        red_black_tree* uncle = (par==grandpar->left) ? grandpar->right : grandpar->left;
        if (uncle != nullptr and uncle->color == "red") {
            add_all_we_do_to_file("--> Оба родителя красные, перекрашиваем", "output_ans.txt");
            par->color = "black";
            uncle->color = "black";
            grandpar->color = "red";
            child = grandpar;
        }
        else {
            if (child == par->right && par == grandpar->left) {
                rotation_to_left(tree, par);
                child = par;
                par = child->parent;
            }
            else if (child == par->left && par == grandpar->right) {
                rotation_to_right(tree, par);
                child = par;
                par = child->parent;
            }
            par->color = "black";
            grandpar->color = "red";
            add_all_we_do_to_file("--> Выполняем вращение для балансировки", "output_ans.txt");
            if (par == grandpar->left) {
                rotation_to_right(tree, grandpar);
                if (tree == grandpar) {
                    tree = par;
                }
            }
            else {
                rotation_to_left(tree, grandpar);
                if (tree == grandpar) {
                    tree = par;
                }
            }
        }
    }
    tree->color = "black";
    end_time = steady_clock::now();
    result1 = duration_cast<nanoseconds>(end_time - start_time);
    add_all_we_do_to_file("--> Устанавливаем цвет корня - черным", "output_ans.txt");
}
void insert_elem_in_red_black_tree(red_black_tree*& tree, int num, bool need_duration){
    add_all_we_do_to_file("--> Вставляем элемент: " + to_string(num), "output_ans.txt");
    red_black_tree* new_elem = new red_black_tree;
    time_point<steady_clock, duration<__int64, ratio<1, 1000000000>>>start_time, end_time;
    nanoseconds result;
    start_time = steady_clock::now();
    new_elem->number = num;
    new_elem->color = "red";
    if (tree == nullptr) {
        tree = new_elem;
        tree->color = "black";
        add_all_we_do_to_file("--> Элементов в дереве нет, теперь новый элемент - корень","output_ans.txt");
        return;
    }
    red_black_tree* curr = tree;
    red_black_tree* par = nullptr;
    while (curr !=nullptr) {
        par = curr;
        if (new_elem->number< curr->number) {
            curr = curr->left;
        }
        else {
            curr = curr->right;
        }
    }
    new_elem->parent = par;

    if (new_elem->number < par->number) {
        par->left = new_elem;
    }
    else {
        par->right = new_elem;
    }
    end_time = steady_clock::now();
    result = duration_cast<nanoseconds>(end_time - start_time);
    add_all_we_do_to_file("--> Новый элемент добавлен за " + to_string(result.count()) + " наносекунд, вызываем функцию исправления дерева", "output_ans.txt");
    fix_red_black_tree(tree, new_elem);
    if (need_duration) {
        cout << result.count() << " наносекунд - время добавления элемента в дерево. " << endl;
    }
}
void make_red_black_tree_random(red_black_tree*& tree, int N) {
    int random_numbers[199];
    for (int i = 0; i < 199; ++i) {
        random_numbers[i] = i - 99;
    }
    random_shuffle(random_numbers, random_numbers + 199);
    add_all_we_do_to_file("--> Создаем случайное красно-черное дерево с " + to_string(N) + " элементами", "output_ans.txt");
    int random_num;
    for (int i = 0; i < N; i++) {
        random_num = random_numbers[i % 199];
        cout << random_num << endl;
        add_all_we_do_to_file("--> Генерируем случайный элемент: " + to_string(random_num), "output_ans.txt");
        insert_elem_in_red_black_tree(tree, random_num, false);
    }
}
void make_red_black_tree_hand_input(red_black_tree*& tree, int N) {
    string array_nums = "";
    cin.ignore();
    while (true) {
        getline(cin, array_nums);
        if (array_nums.empty()) {
            break;
        }
        else {
            int number = stoi(array_nums);
            insert_elem_in_red_black_tree(tree, number, false);
            N++;
        }
    }
}
void change_in_tree(red_black_tree*& tree, red_black_tree* num1, red_black_tree* num2) {
    if (num1->parent == nullptr) {
        tree = num2; 
    }
    else if (num1 == num1->parent->left) {
        num1->parent->left = num2; 
    }
    else {
        num1->parent->right = num2; 
    }
    if (num2 != nullptr) {
        num2->parent = num1->parent; 
    }
}
red_black_tree* min_in_tree(red_black_tree*& tree) {
    while (tree->left != nullptr) {
        tree = tree->left;
    }
    return tree;

}
void fix_deleting(red_black_tree*& tree, red_black_tree*& child) {
    while (child != tree && child->color == "black") {
        if (child == child->parent->left) {
            red_black_tree* brother = child->parent->right;

            if (brother && brother->color == "red") { 
                brother->color = "black";
                child->parent->color = "red";
                rotation_to_left(tree, child->parent);
                brother = child->parent->right; 
            }
            if ((brother == nullptr || brother->left == nullptr || brother->left->color == "black") &&
                (brother == nullptr || brother->right == nullptr || brother->right->color == "black")) {
                brother->color = "red";
                child = child->parent;
            }
            else {
                if (brother && brother->right == nullptr || brother->right->color == "black") {
                    if (brother->left != nullptr) {
                        brother->left->color = "black";
                    }
                    brother->color = "red";
                    rotation_to_right(tree, brother);
                    brother = child->parent->right;
                }
                brother->color = child->parent->color;
                child->parent->color = "black";
                if (brother->right != nullptr) {
                    brother->right->color = "black";
                }
                rotation_to_left(tree, child->parent);
                break;
            }
        }
        else { // Если - правый ребенок
            red_black_tree* brother = child->parent->left;

            if (brother && brother->color == "red") {
                brother->color = "black";
                child->parent->color = "red";
                rotation_to_right(tree, child->parent);
                brother = child->parent->left; 
            }

            if ((brother == nullptr || brother->left == nullptr || brother->left->color == "black") &&
                (brother == nullptr || brother->right == nullptr || brother->right->color == "black")) {
                brother->color = "red";
                child = child-> parent;
            }
            else {
                if (brother && brother ->left == nullptr || brother -> left -> color == "black") {
                    if (brother -> right != nullptr) {
                        brother -> right -> color = "black";
                    }
                    brother -> color = "red";
                    rotation_to_left(tree, brother);
                    brother = child->parent-> left;
                }

                brother -> color = child-> parent->color;
                child-> parent->color = "black";

                if (brother -> left != nullptr) {
                    brother -> left ->color = "black";
                }
                rotation_to_right(tree, child-> parent);
                break;
            }
        }
    }
    child->color = "black";
    tree->color = "black";
}
bool delete_elem(red_black_tree* tree, int num) {
    time_point<steady_clock, duration<__int64, ratio<1, 1000000000>>>start_time, end_time;
    nanoseconds result;
    start_time = steady_clock::now();
    red_black_tree* curr = tree;
    while (curr != nullptr && curr->number != num) {
        if (num < curr->number) {
            curr = curr->left;
        }
        else {
            curr = curr->right;
        }
    }

    if (curr == nullptr) {
        cout << "Элемент " << num << " не найден." << std::endl;
        return false;
    }

    red_black_tree* y = nullptr;
    red_black_tree* child = nullptr;
    string or_color = curr->color;

    if (curr->left == nullptr) {
        child = curr->right;
        change_in_tree(tree, curr, curr->right);
    }
    else if (curr->right == nullptr) {
        child = curr->left;
        change_in_tree(tree, curr, curr->left);
    }
    else {
        y = min_in_tree(curr->right);
        or_color = y->color;
        child = y->right;

        if (y->parent == curr) {
            if (child != nullptr) {
                child->parent = y;
            }
        }
        else {
            change_in_tree(tree, y, y->right);
            y->right = curr->right;
            y->right->parent = y;
        }
        change_in_tree(tree, curr, y);
        y->left = curr->left;
        y->left->parent = y;
        y->color = curr->color;
    }

    delete curr;

    if (or_color == "black") {
        fix_deleting(tree, child);
    }
    end_time = steady_clock::now();
    result = duration_cast<nanoseconds>(end_time - start_time);
    cout << result.count() << " наносекунд - время удаления элемента из дерева. " << endl;
    add_all_we_do_to_file(to_string(result.count()) + " наносекунд - время удаления элемента из дерева.", "output_key.txt");
    return true;
}
red_black_tree* find_elem(red_black_tree* tree, int num) {
    time_point<steady_clock, duration<__int64, ratio<1, 1000000000>>>start_time, end_time;
    nanoseconds result;
    start_time = steady_clock::now();
    while (tree != nullptr && tree->number != num) {
        if (num < tree->number) {
            tree = tree->left;
        }
        else {
            tree = tree->right;
        }
    }
    end_time = steady_clock::now();
    result = duration_cast<nanoseconds>(end_time - start_time);
    cout << result.count() << " наносекунд - время поиска элемента в дерево. " << endl;
    add_all_we_do_to_file(to_string(result.count()) + " наносекунд - время поиска элемента в дерево. ", "output_key.txt");
    return tree;
}
void generate_tasks(red_black_tree *& tree, int num_tasks) {
    ofstream file1("output_ans.txt", ios::trunc);
    file1.close();
    ofstream file2("output_key.txt", ios::trunc);
    file2.close();
    ofstream file3("output_task.txt", ios::trunc);
    file3.close();
    if (num_tasks <= 0) {
        cout << "Получается заданий нет" << endl;
        add_all_we_do_to_file("Получается заданий нет", "output_task.txt");
        add_all_we_do_to_file("Заданий нет, ответов тоже", "output_ans.txt");
        add_all_we_do_to_file("Получается ответов нет", "output_key.txt");
        return;
    }
    string tasks[] = {
        "Создать красно-черное дерево.",
        "Вывести красно-черное дерево.",
        "Вставка элемента",
        "Удаление элемента",
        "Поиск элемента"
    };
    const int num_tasks_options = sizeof(tasks) / sizeof(tasks[0]);
    int random_numbers[199];
    for (int i = 0; i < 199; ++i) {
        random_numbers[i] = i - 99; 
    }
    random_shuffle(random_numbers, random_numbers + 199);
    srand(time(0));
    int random_element = random_numbers[0]; 
    tree = nullptr;
    add_all_we_do_to_file(to_string(1) + ". " + tasks[0], "output_task.txt");
    make_red_black_tree_random(tree, random_element);
    add_all_we_do_to_file("Красно-черное дерево из " + to_string(random_element) + " элементов сформировано.", "output_key.txt");
    for (int i = 0; i < num_tasks-1; ++i) {
        int task_index = rand() % num_tasks_options;
        cout << (i + 2) << ". " << tasks[task_index] << endl;
        add_all_we_do_to_file(to_string((i + 2)) + ". " + tasks[task_index], "output_task.txt");
        if (task_index == 2 or task_index == 3 or task_index == 4) {
            int random_element = random_numbers[i % 199];
            add_all_we_do_to_file("Случайный элемент для операции: " + to_string(random_element), "output_task.txt");
            if (task_index == 2) {
                while (find_elem(tree, random_element)) {
                    add_all_we_do_to_file("Элемент " + to_string(random_element) + " уже есть в дереве. Введите другой элемент для вставки.", "output_ans.txt");
                    random_element = random_numbers[i % 199];
                }
                insert_elem_in_red_black_tree(tree, random_element, true);
                add_all_we_do_to_file("Элемент " + to_string(random_element) + " вставлен в дерево.", "output_key.txt");
            }
            else if (task_index == 3) {
                if (delete_elem(tree, random_element)) {
                    add_all_we_do_to_file("Элемент " + to_string(random_element) + "удален.", "output_key.txt");
                }
                else {
                    add_all_we_do_to_file("Элемент " + to_string(random_element) + " не найден и не удален.", "output_key.txt");
                }
            }
            else if (task_index == 4) {
                if (find_elem(tree, random_element)) {
                    add_all_we_do_to_file("Элемент " + to_string(random_element) + " найден.", "output_key.txt");
                }
                else {
                    add_all_we_do_to_file("Элемент " + to_string(random_element) + " не найден.", "output_key.txt");
                }
            }
            else if (task_index == 0) {
                tree = nullptr;
                make_red_black_tree_random(tree, random_element);
                add_all_we_do_to_file("Красно-черное дерево из " + to_string(random_element) + " элементов сформировано.", "output_key.txt");
            }
        }
        else if (task_index == 1) {
            print_tree(tree);
            add_all_we_do_to_file("Красно-черное дерево выведено на экран.", "output_key.txt");
        }
    }
}
void display_menu() {
    cout << "Выберите действие:" << endl;
    cout << "1. Создать красно-черное дерево." << endl;
    cout << "2. Вывести красно-черное дерево." << endl;
    cout << "3. Определение скорости вставки, удаления и получения элемента дерева." << endl;
    cout << "4. Генерация заданий к практической работе по красно-черным деревьям. " << endl;
    cout << "6. Выход!" << endl;
}
int main(){
    red_black_tree* tree = nullptr;
    setlocale(0, "");
    int identificator, i, N, num, result=0, num_tasks;
    string res;
    while (true) {
        display_menu();
        cout << "ВВЕДИТЕ НОМЕР ЗАДАНИЯ: ";
        cin >> identificator;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        system("cls");
        switch (identificator) {
        case 1:
            cout << "Формирование красно-черного дерева из N элементов:\
 1) пользователь вводит количество элементов N красно-черного дерева, которое автоматически заполняется случайными числами(–99 до 99);\
2) пользователь вводит в консоль элементы массива, N определяется автоматически по количеству введенных элементов; " << endl;
            cout << "ВВЕДИТЕ 1 или 2: ";
            cin >> i;
            switch (i) {
            case 1:
                cout << "Введите число элементов" << endl;
                cin >> N;
                tree = nullptr;
                make_red_black_tree_random(tree, N);
                print_tree(tree);
                break;
            case 2:
                N = 0;
                tree = nullptr;
                make_red_black_tree_hand_input(tree, N);
                print_tree(tree);
                break;
            default:
                cout << "Некорректный номер задания." << endl;
                break;
            }
            break;
        case 2:
            print_tree(tree);
            break;
        case 3:
            cout << "Формирование красно-черного дерева из N элементов: 1) вставка элемента 2) удаление элемента 3) получения элемента" << endl;
            cout << "ВВЕДИТЕ 1 или 2 или 3: ";
            cin >> i;
            switch (i) {
            case 1:
                cout << "Введите число для вставки: " << endl;
                cin >> num;
                while (find_elem(tree, num)) {
                    res = "Элемент " + to_string(num) + " уже есть в дереве. Введите другой элемент для вставки.";
                    cout << res << endl;
                    cin >> num;
                }
                insert_elem_in_red_black_tree(tree, num, true);
                print_tree(tree);
                break;
            case 2:
                N = 0;
                cout << "Введите число для удаления: " << endl;
                cin >> num;
                if (delete_elem(tree,num)) {
                    res = "Элемент " + to_string(num) + " удален.";
                    cout << res << endl;
                    print_tree(tree);
                }
                else {
                    res = "Элемент " + to_string(num) + "не найден и не удален.";
                    cout << res << endl;
                }
                break;
            case 3:
                cout << "Введите число для поиска: " << endl;
                cin >> num;
               if (find_elem(tree, num)) {
                    res = "Элемент " + to_string(num) + " найден.";
                    cout << res<<endl;
                }
                else {
                    res = "Элемент " + to_string(num) + " не найден.";
                    cout << res << endl;
                }
                break;
            default:
                cout << "Некорректный номер задания." << endl;
                break;
            }
            break;
        case 4:
            cout << "Введите количество рандомных заданий " << endl;
            cin >> num_tasks;
            generate_tasks(tree, num_tasks);
            break;
        case 6:
            cout << "Выход!" << endl;
            return 0;
        default:
            cout << "Некорректный номер задания." << endl;
            break;
        }
        cout << "Задание выполнено. Нажмите Enter, чтобы продолжить." << endl;
        cin.ignore();
        cin.get();
    }
    return 0;
}
