#include "menu.h"
#include "writer.h"

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Writer writer;
	menu_process(
		Menu(
			"WRITER",
			"Exit",
			std::vector<Item>({
				Item("Project file", [&writer]() { writer.ProjectFile(); }),
				Item("Write", [&writer]() { writer.Write(); }),
				Item("Close", [&writer]() { writer.Close(); })
				})
			)
	);
}
