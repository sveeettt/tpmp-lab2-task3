#ifndef ABONENT_H
#define ABONENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ABONENTS 10
#define NAME_LEN 50
#define PHONE_LEN 15
#define TARIFF_LEN 20

typedef struct {
    int year;
    int month;
    int day;
} Date;

typedef struct {
    char fullName[NAME_LEN];      // фамилия и инициалы
    char phoneNumber[PHONE_LEN];   // номер телефона
    Date connectionDate;           // дата подключения
    char tariffPlan[TARIFF_LEN];   // тарифный план
    float accruedAmount;           // начисленная сумма оплаты
    float accountBalance;          // сумма на счёту абонента
} Abonent;

int createAbonents(Abonent abonents[], int maxSize);
void sortAbonentsByName(Abonent abonents[], int count);
void addBonusForOldAbonents(Abonent abonents[], int count, int currentYear);
void printDebtors(const Abonent abonents[], int count);
void printTariffStatistics(const Abonent abonents[], int count);
void printAllAbonents(const Abonent abonents[], int count);


int getCurrentYear(void);
void printAbonent(const Abonent *a);
void clearInputBuffer(void);

#endif
