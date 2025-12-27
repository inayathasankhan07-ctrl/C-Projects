// Restaurant Billing System
#include <stdio.h>
#include <string.h>

struct MenuItem {
    int id;
    char name[50];
    float price;
};

struct OrderItem {
    int id;
    char name[50];
    int quantity;
    float unit_price;
    float amount;
};

// Function to calculate the bill
void generate_bill(struct OrderItem items[], int count) {
    float sub_total = 0;
    float discount_rate = 10.0; // 10% discount
    float gst_rate = 18.0;     // 18% GST

    printf("\n\n**************************** INVOICE ****************************\n");
    printf("ID\tName\t\tQty\tUnit Price\tAmount\n");
    printf("---------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        items[i].amount = items[i].quantity * items[i].unit_price;
        sub_total += items[i].amount;
        printf("%d\t%-15s\t%d\t%.2f\t\t%.2f\n", items[i].id, items[i].name, items[i].quantity, items[i].unit_price, items[i].amount);
    }

    float discount_amount = sub_total * (discount_rate / 100.0);
    float taxable_value = sub_total - discount_amount;
    float gst_amount = taxable_value * (gst_rate / 100.0);
    float total_bill = taxable_value + gst_amount;

    printf("---------------------------------------------------------------\n");
    printf("Sub Total:\t\t\t\t%.2f\n", sub_total);
    printf("Discount (%.1f%%):\t\t\t-%.2f\n", discount_rate, discount_amount);
    printf("Taxable Value:\t\t\t\t%.2f\n", taxable_value);
    printf("GST (%.1f%%):\t\t\t\t%.2f\n", gst_rate, gst_amount);
    printf("---------------------------------------------------------------\n");
    printf("Total Amount Payable:\t\t\t%.2f\n", total_bill);
    printf("*************************************************************\n");
}

int main() {
    struct MenuItem menu[] = {
        {1, "Burger", 150.0},
        {2, "Pizza", 450.0},
        {3, "Pasta", 200.0},
        {4, "Soft Drink", 50.0}
    };
    int menu_size = sizeof(menu) / sizeof(menu[0]);
    struct OrderItem customer_orders[100]; // Array to store order items
    int order_count = 0;
    char add_more = 'y';

    printf("Welcome to the C Billing System\n");

    while (add_more == 'y' || add_more == 'Y') {
        printf("\n--- Menu ---\n");
        printf("ID\tName\t\tPrice\n");
        for (int i = 0; i < menu_size; i++) {
            printf("%d\t%-15s\t%.2f\n", menu[i].id, menu[i].name, menu[i].price);
        }
        printf("------------\n");

        int item_id, quantity;
        printf("Enter the item ID: ");
        scanf("%d", &item_id);
        printf("Enter quantity: ");
        scanf("%d", &quantity);

        int found = 0;
        for (int i = 0; i < menu_size; i++) {
            if (menu[i].id == item_id) {
                customer_orders[order_count].id = item_id;
                strcpy(customer_orders[order_count].name, menu[i].name);
                customer_orders[order_count].quantity = quantity;
                customer_orders[order_count].unit_price = menu[i].price;
                order_count++;
                found = 1;
                break;
            }
        }

        if (!found) {
            printf("Invalid item ID. Please try again.\n");
        }

        printf("Do you want to add more items? (y/n): ");
        scanf(" %c", &add_more);
    }

    if (order_count > 0) {
        generate_bill(customer_orders, order_count);
    } else {
        printf("No items ordered. Exiting.\n");
    }

    return 0;
}
