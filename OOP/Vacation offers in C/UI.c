#define _CRT_SECURE_NO_WARNINGS
#include "Controller.h"
#include "Repository.h"
#include "UI.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "DynamicUndoRedo.h"

UI* create_ui(Controller* controller)
{
	UI* ui = malloc(sizeof(UI));
	if (ui != NULL)
		ui->c = controller;
	return ui;
}

void destroy_ui(UI* ui)
{
	if (ui == NULL)
		return;
	destroy_controller(ui->c);
	free(ui);
}

void menu()
{
	printf("1) Add an offer.\n");
	printf("2) Remove an offer.\n");
	printf("3) Update an offer.\n");
	printf("4) Display all the offers.\n");
	printf("5) Display all tourism offers whose destinations contain a given string, and show them sorted ascending by price.\n");
	printf("6) Display all offers of a given type, having their departure after a given date.\n");
	printf("7) Undo.\n");
	printf("8) Redo.\n");
	printf("9) Exit\n");
}

void print_offers(Controller* c)
{
	if (c->repo->offers->size == 0)
		printf("No current offers.\n");
	int i;
	for (i = 0; i < c->repo->offers->size; i++)
		printf("The offer number %d <> Type: %s | Destination: %s | Departure date: %s | Price: %d\n", i + 1, c->repo->offers->elems[i]->type,
			c->repo->offers->elems[i]->destination, c->repo->offers->elems[i]->departure_date, c->repo->offers->elems[i]->price);
	printf("\n");
}

void print_search_string_destination(UI* ui, char* string)
{
	DynamicVector* vector = print_search_string_destination_controller(ui->c, string);
	for (int i = 0; i < vector->size; i++)
		printf("The offer number %d <> Type: %s | Destination: %s | Departure date: %s | Price: %d\n", i + 1, vector->elems[i]->type, vector->elems[i]->destination,
			vector->elems[i]->departure_date, vector->elems[i]->price);
	if (vector->size == 0)
		printf("No current offers.\n");
	printf("\n");

	free(vector->elems);
	free(vector);
}

void print_search_string_type_date(UI* ui, char* type, char* date)
{
	if (strlen(date) != 10)
		printf("The date is invalid.\n\n");

	DynamicVector* vector = print_search_string_type_date_controller(ui->c, type, date);

	for (int i = 0; i < vector->size; i++)
		printf("The offer number %d <> Type: %s | Destination: %s | Departure date: %s | Price: %d\n", i + 1, vector->elems[i]->type, vector->elems[i]->destination,
			vector->elems[i]->departure_date, vector->elems[i]->price);
	if (vector->size == 0)
		printf("No current offers.\n");
	printf("\n");

	free(vector->elems);
	free(vector);
}

int check_command(int command)
{
	if (command != 1 && command != 2 && command != 3 && command != 4 && command != 5 && command != 6 && command != 7 &&  command != 8 && command != 9)
		return 0;
	return 1;
}

int check_undo_redo(int command)
{
	if (command == 1 || command == 2 || command == 3)
		return 0;
	return 1;
}

void start_ui(UI* ui)
{
	DynamicUndoRedo* undo_operation = create_dynamic_undo_redo(50, &free_dynamic_undo_redo);
	DynamicUndoRedo* redo_operation = create_dynamic_undo_redo(50, &free_dynamic_undo_redo);
	int ok = 1;
	int undo_redo = 0;
	while (ok == 1)
	{
		menu();
		printf("Please enter your command: ");
		int command;
		scanf("%d", &command);
		while (getchar() != '\n')
			;
		if (check_command(command) == 1)
		{
			if (command == 9)
			{
				printf("Exiting...\n");
				free_dynamic_undo_redo(undo_operation);
				free_dynamic_undo_redo(redo_operation);
				free(undo_operation->elems);
				free(redo_operation->elems);
				free(undo_operation);
				free(redo_operation);
				return;
			}
			if (check_undo_redo(command) == 0 && undo_redo == 1)
			{
				undo_redo = 0;
				free_dynamic_undo_redo(undo_operation);
				free_dynamic_undo_redo(redo_operation);
			}
			printf("\n");
			if (command == 1)
			{
				char type[20], destination[20], departure_date[20];
				int price;
				printf("The type of the offer is: ");
				gets(type);
				printf("The destination of the offer is: ");
				gets(destination);
				printf("The departure date of the offer is (format -> dd/mm/yyyy): ");
				gets(departure_date);
				printf("The price of the offer is (must be an integer): ");
				scanf("%d", &price);
				add_dynamic_undo_redo(undo_operation, make_a_copy_dynamic_undo_redo(ui->c->repo->offers));
				while (getchar() != '\n')
					;
				if (add_controller(ui->c, type, destination, departure_date, price) == 1)
					printf("Succesfully added new offer.\n\n");
				else
				{
					printf("This offer can not be added.\n\n");
					undo_operation->size -= 1;
					undo_operation->destroy(undo_operation->elems[undo_operation->size]);
				}
			}
			if (command == 2)
			{
				char destination[20], departure_date[20];
				printf("The destination of the offer you want to remove is: ");
				gets(destination);
				printf("The departure date of the offer you want to remove is (format -> yyyy/mm/dd): ");
				gets(departure_date);
				add_dynamic_undo_redo(undo_operation, make_a_copy_dynamic_undo_redo(ui->c->repo->offers));
				if (remove_controller(ui->c, destination, departure_date) == 1)
					printf("Succesfully removed the offer.\n\n");
				else
				{
					printf("This offer can not be removed.\n\n");
					undo_operation->size -= 1;
					undo_operation->destroy(undo_operation->elems[undo_operation->size]);
				}
			}
			if (command == 3)
			{
				char destination[20], departure_date[20], type[20];
				int price;
				printf("The destination of the offer you want to update is: ");
				gets(destination);
				printf("The departure date of the offer you want to update is (format -> yyyy/mm/dd): ");
				gets(departure_date);
				printf("The new type is (-1 if you do not want to change it): ");
				gets(type);
				printf("The new price is (-1 if you do not want to change it, must be an integer): ");
				scanf("%d", &price);
				while (getchar() != '\n')
					;
				add_dynamic_undo_redo(undo_operation, make_a_copy_dynamic_undo_redo(ui->c->repo->offers));
				if (update_controller(ui->c, destination, departure_date, type, price) == 1)
					printf("Succesfully updated the offer.\n\n");
				else
				{
					printf("This offer can not be updated.\n\n");
					undo_operation->size -= 1;
					undo_operation->destroy(undo_operation->elems[undo_operation->size]);
				}
			}
			if (command == 4)
			{
				print_offers(ui->c);
			}
			if (command == 5)
			{
				char string[20];
				printf("The string is: ");
				gets(string);
				printf("\n");
				print_search_string_destination(ui, string);
			}
			if (command == 6)
			{
				char type[20], data[20];
				printf("The type is: ");
				gets(type);
				printf("The date is (format -> yyyy/mm/dd): ");
				gets(data);
				printf("\n");
				print_search_string_type_date(ui, type, data);
			}
			if (command == 7)
			{
				if (undo_operation->size == 0)
					printf("Can not undo.\n\n");
				else
				{
					undo_redo = 1;
					add_dynamic_undo_redo(redo_operation, make_a_copy_dynamic_undo_redo(ui->c->repo->offers));
					ui->c->repo->offers = make_a_copy_dynamic_undo_redo(undo_operation->elems[undo_operation->size - 1]);
					undo_operation->size--;
					undo_operation->destroy(undo_operation->elems[undo_operation->size]);
					printf("Undo succesful.\n\n");
				}
			}
			if (command == 8)
			{
				if (redo_operation->size == 0)
					printf("Can not redo.\n\n");
				else
				{
					undo_redo = 1;
					undo_operation->elems[undo_operation->size++] = make_a_copy_dynamic_undo_redo(ui->c->repo->offers);
					ui->c->repo->offers = make_a_copy_dynamic_undo_redo(redo_operation->elems[redo_operation->size - 1]);
					redo_operation->size--;
					redo_operation->destroy(redo_operation->elems[redo_operation->size]);
					printf("Redo succesful.\n\n");
				}
			}
		}
		else
			printf("\nPlease enter a valid command!\n\n");
	}
}
