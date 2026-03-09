#include "abonent.h"

void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int getCurrentYear(void) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    return tm.tm_year + 1900;
}

int createAbonents(Abonent abonents[], int maxSize) {
    int count;
    
    printf("Введите количество абонентов (не более %d): ", maxSize);
    scanf("%d", &count);
    clearInputBuffer();
    
    if (count <= 0 || count > maxSize) {
        printf("Ошибка: количество должно быть от 1 до %d\n", maxSize);
        return 0;
    }
    
    for (int i = 0; i < count; i++) {
        printf("\n--- Ввод данных для абонента %d ---\n", i + 1);
         
        printf("Фамилия и инициалы: ");
        fgets(abonents[i].fullName, NAME_LEN, stdin);
        abonents[i].fullName[strcspn(abonents[i].fullName, "\n")] = 0;
        
        printf("Номер телефона: ");
        fgets(abonents[i].phoneNumber, PHONE_LEN, stdin);
        abonents[i].phoneNumber[strcspn(abonents[i].phoneNumber, "\n")] = 0;
        
        printf("Дата подключения (год месяц день): ");
        scanf("%d %d %d", 
              &abonents[i].connectionDate.year,
              &abonents[i].connectionDate.month,
              &abonents[i].connectionDate.day);
        clearInputBuffer();
        
        printf("Тарифный план: ");
        fgets(abonents[i].tariffPlan, TARIFF_LEN, stdin);
        abonents[i].tariffPlan[strcspn(abonents[i].tariffPlan, "\n")] = 0;
        
        printf("Начисленная сумма оплаты: ");
        scanf("%f", &abonents[i].accruedAmount);
        
        printf("Сумма на счёту абонента: ");
        scanf("%f", &abonents[i].accountBalance);
        clearInputBuffer();
    }
    
    return count;
}

    static int compareNames(const void *a, const void *b) {
    const Abonent *abA = (const Abonent*)a;
    const Abonent *abB = (const Abonent*)b;
    return strcmp(abA->fullName, abB->fullName);
}


void sortAbonentsByName(Abonent abonents[], int count) {
    qsort(abonents, count, sizeof(Abonent), compareNames);
    printf("\n✓ Абоненты отсортированы по алфавиту.\n");
}


static int isMoreThan10YearsAgo(const Date *connectionDate, int currentYear) {
    return (currentYear - connectionDate->year) > 10;
}

// Добавить 10 руб. на счета абонентов, подключенных более 10 лет назад
void addBonusForOldAbonents(Abonent abonents[], int count, int currentYear) {
    int bonusCount = 0;
    
    for (int i = 0; i < count; i++) {
        if (isMoreThan10YearsAgo(&abonents[i].connectionDate, currentYear)) {
            abonents[i].accountBalance += 10.0;
            bonusCount++;
        }
    }
    
    printf("\n✓ Бонус начислен %d абонентам (подключенным более 10 лет назад).\n", bonusCount);
}


void printDebtors(const Abonent abonents[], int count) {
    int debtorCount = 0;
    float balanceAfterDeduction;
    
    printf("\n--- Абоненты с отрицательным балансом после вычета начислений ---\n");
    
    for (int i = 0; i < count; i++) {
        balanceAfterDeduction = abonents[i].accountBalance - abonents[i].accruedAmount;
        
        if (balanceAfterDeduction < 0) {
            debtorCount++;
            printf("\nАбонент %d:\n", debtorCount);
            printAbonent(&abonents[i]);
            printf("Баланс после вычета начислений: %.2f руб.\n", balanceAfterDeduction);
        }
    }
    
    if (debtorCount == 0) {
        printf("Нет абонентов с отрицательным балансом после вычета начислений.\n");
    }
}


void printTariffStatistics(const Abonent abonents[], int count) {
    typedef struct {
        char name[TARIFF_LEN];
        int quantity;
    } TariffStat;
    
    TariffStat tariffs[MAX_ABONENTS];
    int uniqueTariffs = 0;
    
    for (int i = 0; i < count; i++) {
        int found = 0;
        
        for (int j = 0; j < uniqueTariffs; j++) {
            if (strcmp(tariffs[j].name, abonents[i].tariffPlan) == 0) {
                tariffs[j].quantity++;
                found = 1;
                break;
            }
        }
        
        if (!found && uniqueTariffs < MAX_ABONENTS) {
            strcpy(tariffs[uniqueTariffs].name, abonents[i].tariffPlan);
            tariffs[uniqueTariffs].quantity = 1;
            uniqueTariffs++;
        }
    }
    
    
    printf("\n--- Статистика по тарифным планам ---\n");
    for (int i = 0; i < uniqueTariffs; i++) {
        printf("%s: %d абонентов\n", tariffs[i].name, tariffs[i].quantity);
    }
}


void printAllAbonents(const Abonent abonents[], int count) {
    if (count == 0) {
        printf("Нет данных об абонентах.\n");
        return;
    }
    
    printf("\n--- Список всех абонентов ---\n");
    for (int i = 0; i < count; i++) {
        printf("\nАбонент %d:\n", i + 1);
        printAbonent(&abonents[i]);
    }
}


void printAbonent(const Abonent *a) {
    printf("  ФИО: %s\n", a->fullName);
    printf("  Телефон: %s\n", a->phoneNumber);
    printf("  Дата подключения: %04d-%02d-%02d\n", 
           a->connectionDate.year, 
           a->connectionDate.month, 
           a->connectionDate.day);
    printf("  Тариф: %s\n", a->tariffPlan);
    printf("  Начислено: %.2f руб.\n", a->accruedAmount);
    printf("  На счету: %.2f руб.\n", a->accountBalance);
}
