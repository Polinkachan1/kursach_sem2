#include <iostream>
#include <string>
#include <iomanip>
using namespace std;


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
    cout << tree->number << " (" << tree->color << ")" << endl;
    print_tree(tree->left, level + 1);
}
void rotation_to_left(red_black_tree*& tree, red_black_tree*& elem) {
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
    while (child != tree && child->parent != nullptr && child->parent->color == "red") {
        red_black_tree* par = child->parent;
        red_black_tree* grandpar = par->parent;
        red_black_tree* uncle = (par==grandpar->left) ? grandpar->right : grandpar->left;
        if (uncle != nullptr and uncle->color == "red") {
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
            if (par == grandpar->left) {
                rotation_to_right(tree, grandpar);
            }
            else {
                rotation_to_left(tree, grandpar);
            }
        }
    }
    tree->color = "black";
}
void insert_elem_in_red_black_tree(red_black_tree*& tree, int num) {
    red_black_tree* new_elem = new red_black_tree;
    new_elem->number = num;
    new_elem->color = "red";
    if (tree == nullptr) {
        tree = new_elem;
        tree->color = "black";
        return;
    }
    red_black_tree* curr = tree;
    red_black_tree* par = nullptr;
    while (curr !=nullptr) {
        par = curr;
        if (new_elem->number < curr->number) {
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
    fix_red_black_tree(tree, new_elem);
}
void make_red_black_tree_random(red_black_tree *& tree, int N){
    srand(time(0));
    int random_num;
    for (int i = 0; i < N; i++) {
         random_num = rand() % 199 - 99;
         insert_elem_in_red_black_tree(tree, random_num);
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
            insert_elem_in_red_black_tree(tree, number);
            N++;
        }
    }
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
    int identificator, i, res, N;
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
                make_red_black_tree_random(tree, N);
                print_tree(tree);
                break;
            case 2:
                N = 0;
                make_red_black_tree_hand_input(tree,N);
                print_tree(tree);
                break;
            default:
                cout << "Некорректный номер задания." << endl;
                break;
            }
            break;
        case 2:
            break;
        case 3:
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
