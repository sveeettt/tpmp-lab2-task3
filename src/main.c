#include "abonent.h"

int main(void) {
    Abonent abonents[MAX_ABONENTS];
    int count = 0;
    int choice;
    int currentYear = getCurrentYear();
    
    printf("   Лабораторная работа №2, Задание 3\n");
    
    
    while (1) {
        printf("               МЕНЮ                 \n");
        
        printf(" 1. Ввод данных об абонентах       \n");
        printf(" 2. Сортировка по алфавиту         \n");
        printf(" 3. Начислить бонус (стаж >10 лет) \n");
        printf(" 4. Показать должников             \n");
        printf(" 5. Статистика по тарифам          \n");
        printf(" 6. Вывести всех абонентов         \n");
        printf(" 0. Выход                           \n");
        
        printf("Выберите действие: ");
        scanf("%d", &choice);
        clearInputBuffer();
        
        switch (choice) {
            case 1:
                count = createAbonents(abonents, MAX_ABONENTS);
                break;
                
            case 2:
                if (count > 0) {
                    sortAbonentsByName(abonents, count);
                } else {
                    printf("Сначала введите данные об абонентах.\n");
                }
                break;
                
            case 3:
                if (count > 0) {
                    addBonusForOldAbonents(abonents, count, currentYear);
                } else {
                    printf("Сначала введите данные об абонентах.\n");
                }
                break;
                
            case 4:
                if (count > 0) {
                    printDebtors(abonents, count);
                } else {
                    printf("Сначала введите данные об абонентах.\n");
                }
                break;
                
            case 5:
                if (count > 0) {
                    printTariffStatistics(abonents, count);
                } else {
                    printf("Сначала введите данные об абонентах.\n");
                }
                break;
                
            case 6:
                printAllAbonents(abonents, count);
                break;
                
            case 0:
                printf("Программа завершена.\n");
                return 0;
                
            default:
                printf("Неверный выбор. Попробуйте снова.\n");
        }
    }
    
    return 0;
}
