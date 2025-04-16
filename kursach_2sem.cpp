#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

void add_all_we_do_to_file(const string& what_we_do, string file_name) {
    ofstream file(file_name, ios::app);
    if (file.is_open()) {
        file << what_we_do << endl;
        file.close(); 
    }
    else {
        cerr << "Ошибка при открытии файла для записи." << endl;
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
    add_all_we_do_to_file("--> Устанавливаем цвет корня - черным", "output_ans.txt");
}
void insert_elem_in_red_black_tree(red_black_tree*& tree, int num) {
    add_all_we_do_to_file("--> Вставляем элемент: " + to_string(num), "output_ans.txt");
    red_black_tree* new_elem = new red_black_tree;
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
    add_all_we_do_to_file("--> Новый элемент добавлен, вызываем функцию исправления дерева", "output_ans.txt");
    fix_red_black_tree(tree, new_elem);
}
void make_red_black_tree_random(red_black_tree *& tree, int N){
    srand(time(0));
    add_all_we_do_to_file("--> Создаем случайное красно-черное дерево с " + to_string(N) + " элементами", "output_ans.txt");
    int random_num;
    for (int i = 0; i < N; i++) {
         random_num = rand() % 199 - 99;
         cout << random_num << endl;
         add_all_we_do_to_file("--> Генерируем случайный элемент: " + to_string(random_num), "output_ans.txt");
         insert_elem_in_red_black_tree(tree, random_num);
    }
}
void make_red_black_tree_hand_input(red_black_tree*& tree, int N) {
    string array_nums = "";
    add_all_we_do_to_file("--> Ввод элементов вручную", "output_ans.txt");
    cin.ignore();
    while (true) {
        getline(cin, array_nums);
        if (array_nums.empty()) {
            break;
        }
        else {
            int number = stoi(array_nums);
            add_all_we_do_to_file("--> Вставляем элемент: " + to_string(number), "output_ans.txt");
            insert_elem_in_red_black_tree(tree, number);
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
void fixDeleting(red_black_tree*& tree, red_black_tree*& child) {}
void delete_elem(red_black_tree* tree, int num) {
    red_black_tree * curr = tree;
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
        return; 
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
        fixDeleting(tree, child);
    }
}
red_black_tree* find_elem(red_black_tree* tree, int num) {
    while (tree != nullptr && tree->number != num) {
        if (num < tree->number) {
            tree = tree->left;
        }
        else {
            tree = tree->right;
        }
    }
    return tree; 
}
void display_menu() {
    cout << "Выберите действие:" << endl;
    cout << "1. Создать красно-черное дерево." << endl;
    cout << "2. Вывести красно-черное дерево." << endl;
    cout << "3. Определение скорости вставки, удаления и получения элемента дерева." << endl;
    cout << "4. Определение скорости проверки на сбалансированность." << endl;
    cout << "5. Генерация заданий к практической работе по красно-черным деревьям. " << endl;
    cout << "6. Выход!" << endl;
}
int main(){
    red_black_tree* tree = nullptr;
    setlocale(0, "");
    int identificator, i, N, num;
    string res;
    ofstream file1("output_ans.txt", ios::trunc);
    file1.close();
    ofstream file2("output_key.txt", ios::trunc);
    file2.close();
    ofstream file3("output_task.txt", ios::trunc);
    file3.close();
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
                add_all_we_do_to_file("1)Формирование красно-черного дерева 1) Заполнение дерева рандомными элементами. Количество элементов N=" + to_string(N), "output_task.txt");
                make_red_black_tree_random(tree, N);
                add_all_we_do_to_file("Красно-черное дерево из " + to_string(N)+" элементов сформировано.", "output_key.txt");
                print_tree(tree);
                break;
            case 2:
                N = 0;
                add_all_we_do_to_file("1)Формирование красно-черного дерева 1) Заполнение дерева введенными элементами.", "output_task.txt");
                make_red_black_tree_hand_input(tree, N);
                add_all_we_do_to_file("Красно-черное дерево сформировано.", "output_key.txt");
                print_tree(tree);
                break;
            default:
                cout << "Некорректный номер задания." << endl;
                break;
            }
            break;
        case 2:
            add_all_we_do_to_file("2) Вывод на экран красно-черного дерева.", "output_task.txt");
            cout << "Ваше дерево выглядит так: " << endl;
            print_tree(tree);
            add_all_we_do_to_file("Красно-черное дерево выведено на экран.", "output_key.txt");
            break;
        case 3:
            cout << "Формирование красно-черного дерева из N элементов: 1) вставка элемента 2) удаление элемента 3) получения элемента" << endl;
            cout << "ВВЕДИТЕ 1 или 2 или 3: ";
            cin >> i;
            switch (i) {
            case 1:
                cout << "Введите число для вставки: " << endl;
                cin >> num;
                add_all_we_do_to_file("3.1. Вставка элемента "+to_string(num)+ " в красно - черное дерево.", "output_task.txt");
                insert_elem_in_red_black_tree(tree, num);
                add_all_we_do_to_file("Элемент " + to_string(num) + " вставлен в дерево.", "output_key.txt");
                print_tree(tree);
                break;
            case 2:
                N = 0;
                cout << "Введите число для удаления: " << endl;
                cin >> num;
                add_all_we_do_to_file("3.2. Удаление элемента "+to_string(num)+ " в красно - черном дереве.", "output_task.txt");
                delete_elem(tree, num);
                add_all_we_do_to_file("Элемент " + to_string(num) + " удален.", "output_key.txt");
                print_tree(tree);
                break;
            case 3:
                cout << "Введите число для поиска: " << endl;
                cin >> num;
                add_all_we_do_to_file("3.3. Поиск элемента " + to_string(num) + " в красно - черном дереве.", "output_task.txt");
                if (find_elem(tree, num)) {
                    res = "Элемент " + to_string(num) + " найден.";
                    cout << res<<endl;
                    add_all_we_do_to_file(res, "output_key.txt");
                }
                else {
                    res = "Элемент " + to_string(num) + " не найден.";
                    cout << res << endl;
                    add_all_we_do_to_file(res, "output_key.txt");
                }
                break;
            default:
                cout << "Некорректный номер задания." << endl;
                break;
            }
            break;
            break;
        case 4:
            break;
        case 5:
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
