#include <stdio.h>
#include "Controller.h"
#include "Repository.h"
#include "UI.h"
#include "DynamicVector.h"
#include "DynamicUndoRedo.h"
#include <crtdbg.h>


int main()
{
	test_dynamic_undo_redo();
	test_offer();
	test_dynamic_vector();
	test_repository();
	test_controller();

	DynamicVector* vector = create_dynamic_vector(25, &destroy_offer);
	Repository* repo = create_repository(vector);
	Controller* c = create_controller(repo);
	UI* ui = create_ui(c);
	add_controller(ui->c, "Seaside", "Barcelona", "2020/10/14", 300);
	add_controller(ui->c, "City break", "Atena", "2020/11/17", 210);
	add_controller(ui->c, "Mountain ", "Brasov", "2020/11/18", 280);
	add_controller(ui->c, "Seaside", "Maldives", "2020/11/19", 230);
	add_controller(ui->c, "Mountain ", "Himalaya", "2020/10/12", 820);
	add_controller(ui->c, "Seaside", "Miami", "2020/10/31", 325);
	add_controller(ui->c, "Mountain ", "Everest", "2020/04/01", 620);
	add_controller(ui->c, "Mountain ", "Carpathians", "2020/08/05", 500);
	add_controller(ui->c, "City break ", "Bucharest", "2020/03/27", 200);
	add_controller(ui->c, "City break ", "Paris", "2020/01/02", 250);

	start_ui(ui);
	destroy_ui(ui);

	_CrtDumpMemoryLeaks();

	return 0;
}