#include "coordinate.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

// Global counter for coord_id
int coord_counter = 0;

void add_coordinate(Coordinate* &list_end, float x, float y) {  //new coordinate is added to the end of list
    Coordinate* new_coord = new Coordinate;
    new_coord->x = x;
    new_coord->y = y;
    new_coord->coord_id = ++coord_counter;
    new_coord->next = nullptr;
    new_coord->previous = list_end;

    if (list_end != nullptr) {
        list_end->next = new_coord;
    }
    list_end = new_coord;
}

void forward_display(Coordinate* list_beginning) { //displays coordinates in the order that they were entered/generated
    Coordinate* temp = list_beginning;
    while (temp != nullptr) {
        std::cout << "ID: " << temp->coord_id << " (x: " << temp->x << ", y: " << temp->y << ")\n";
        temp = temp->next;
    }
}

void backward_display(Coordinate* list_end) {   //displays coordinates in the opposite order from which they were added/generated
    Coordinate* temp = list_end;
    while (temp != nullptr) {
        std::cout << "ID: " << temp->coord_id << " (x: " << temp->x << ", y: " << temp->y << ")\n";
        temp = temp->previous;
    }
}

void delete_coordinate(Coordinate* &list_beginning, int coord_id_to_delete) {
    Coordinate* temp = list_beginning;
    while (temp != nullptr && temp->coord_id != coord_id_to_delete) {
        temp = temp->next;
    }
    if (temp == nullptr) return;

    if (temp->previous != nullptr) temp->previous->next = temp->next;
    if (temp->next != nullptr) temp->next->previous = temp->previous;

    if (temp == list_beginning) list_beginning = temp->next;

    delete temp;
}

int list_length(Coordinate* list_beginning) {   //counts the number of coordinates until the end of the list is reached
    int length = 0;
    Coordinate* temp = list_beginning;
    while (temp != nullptr) {
        length++;
        temp = temp->next;
    }
    return length;
}

void closest_to(Coordinate* list_beginning, float x, float y) {
    if (list_beginning == nullptr) return;

    Coordinate* closest = list_beginning;
    float min_distance = std::sqrt(std::pow(list_beginning->x - x, 2) + std::pow(list_beginning->y - y, 2));
    Coordinate* temp = list_beginning->next;

    while (temp != nullptr) {
        float distance = std::sqrt(std::pow(temp->x - x, 2) + std::pow(temp->y - y, 2));
        if (distance < min_distance) {
            closest = temp;
            min_distance = distance;
        }
        temp = temp->next;
    }

    std::cout << "Closest Coordinate ID: " << closest->coord_id << " (x: " << closest->x << ", y: " << closest->y << "), Distance: " << min_distance << "\n";
}


int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <number_of_coordinates>\n";
        return 1;
    }

    int num_coords = std::atoi(argv[1]);
    srand(static_cast<unsigned int>(time(nullptr)));

    Coordinate* list_beginning = nullptr;
    Coordinate* list_end = nullptr;

    // Generate random coordinates and add them to the list
    for (int i = 0; i < num_coords; ++i) {
        float x = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 100.0));
        float y = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 100.0));
        add_coordinate(list_end, x, y);
        if (i == 0) list_beginning = list_end;
    }

    // Display the list from beginning to end
    std::cout << "Forward display of coordinates:\n";
    forward_display(list_beginning);

    // Display the list from end to beginning
    std::cout << "\nBackward display of coordinates:\n";
    backward_display(list_end);

    // Print the length of the list
    std::cout << "\nList Length: " << list_length(list_beginning) << "\n";

    // Delete a coordinate with coord_id = 1 (example)
    std::cout << "\nDeleting coordinate with ID 1...\n";
    delete_coordinate(list_beginning, 1);
    std::cout << "Forward display after deletion:\n";
    forward_display(list_beginning);

    // Find the closest coordinate to (50, 50) (example)
    std::cout << "\nFinding closest coordinate to (50, 50):\n";
    closest_to(list_beginning, 50.0, 50.0);

    return 0;
}
