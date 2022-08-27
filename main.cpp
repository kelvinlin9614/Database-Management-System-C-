/*
 * Author: ZEWEN LIN
 * Project: DATABASE - Final Project
 */
#include "include/SQL.h"

int main(int argc, char *argv[])
{
    SQL sql("_!select.txt");
    sql.run();
    return 0;
}