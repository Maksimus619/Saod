int main() {
    Node* root = NULL;
    int values_count = 100000;

    // Инициализация генератора случайных чисел
    srand((unsigned int)time(NULL));

    // Генерация и добавление случайных значений
    for (int i = 0; i < values_count; i++) {
        int random_value = rand() % (values_count * 10);
        root = insert(root, random_value);
    }

    // Засекаем время перед выполнением операций
    clock_t start_time = clock();

    printf("In-order traversal of the AA tree: ");
    inOrder(root);
    printf("\n");

    printf("Number of nodes in the tree: %d\n", countNodes(root));

    // Добавление случайного значения
    int random_insert_value = rand() % (values_count * 10);
    clock_t insert_start_time = clock();
    if (!isNodePresent(root, random_insert_value)) {
        root = insert(root, random_insert_value);
        printf("Random element added: %d\n", random_insert_value);
    } else {
        printf("Element already exists.\n");
    }
    clock_t insert_end_time = clock();
    double insert_elapsed_time = ((double)(insert_end_time - insert_start_time) * 1000) / CLOCKS_PER_SEC;
    printf("Insert time: %.2f milliseconds\n", insert_elapsed_time);

    // Удаление случайного значения
    int random_delete_value = rand() % (values_count * 10);
    clock_t delete_start_time = clock();
    if (isNodePresent(root, random_delete_value)) {
        root = deleteNode(root, random_delete_value);
        printf("Random element deleted: %d\n", random_delete_value);
    } else {
        printf("Element not found.\n");
    }
    clock_t delete_end_time = clock();
    double delete_elapsed_time = ((double)(delete_end_time - delete_start_time) * 1000) / CLOCKS_PER_SEC;
    printf("Delete time: %.2f milliseconds\n", delete_elapsed_time);

    // Поиск определенного значения
    int search_value = 97;
    clock_t search_start_time = clock();
    SearchResult search_result = search(root, search_value, 1);
    clock_t search_end_time = clock();
    double search_elapsed_time = ((double)(search_end_time - search_start_time) * 1000) / CLOCKS_PER_SEC;

    if (search_result.node) {
        printf("Element with value %d found at level %d.\n", search_value, search_result.level);
    } else {
        printf("Element with value %d not found in the tree.\n", search_value);
    }
    printf("Search time: %.2f milliseconds\n", search_elapsed_time);

    printf("In-order traversal after operations: ");
    inOrder(root);
    printf("\n");

    printf("Number of nodes in the tree after operations: %d\n", countNodes(root));

    // Засекаем время после выполнения операций
    clock_t end_time = clock();
    double elapsed_time = ((double)(end_time - start_time) * 1000) / CLOCKS_PER_SEC;

    printf("Total elapsed time: %.2f milliseconds\n", elapsed_time);

    return 0;
}
