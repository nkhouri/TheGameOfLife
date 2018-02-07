//This demonstrates the cellular automatic system of The Game of Life
//Programmed by Nick Khouri 2/4/18

#include <SFML\Graphics.hpp>
#include <ctime>
#include <iostream>
#include <math.h>

using namespace sf;
using namespace std;

int main() {
	//set the res, width, and height
	//Note: works best when height = width and resolution divides evenly into both
	const int resolution = 5;
	const int width = 1000;
	const int height = 1000;

	int count = 1;
	RenderWindow window(VideoMode(width, height), "The Game of Life");	//create a window
	int grid[width/resolution][height/resolution];	//hold the 1 and 0 vals

	srand((unsigned)time(NULL));					//gen a new seed every instance
	for (int i = 0; i < width / resolution; i++) {
		for (int j = 0; j < height / resolution; j++) {
			grid[i][j] = rand() % 2;				//give a 1 or 0 value into the array
		}
	}


	while (window.isOpen()) {
		//do all the calculations for the next generation
		int nextGen[width/resolution][height/resolution];
		for (int i = 0; i < (width / resolution) - 1; i++) {
			for (int j = 0; j < (height / resolution) - 1; j++) {
				//calculate the sum
				int sum = 0;
				sum += grid[i - 1][j - 1];
				sum += grid[i - 1][j + 1];
				sum += grid[i - 1][j];
				sum += grid[i + 1][j - 1];
				sum += grid[i + 1][j + 1];
				sum += grid[i + 1][j];
				sum += grid[i][j - 1];
				sum += grid[i][j + 1];

				//Condition parameter set
				if (sum < 2 || sum > 3) {								//death condition
					nextGen[i][j] = 0;
				}
				else if (grid[i][j] == 1 && sum == 2 || sum == 3) {		//survival condition
					nextGen[i][j] = 1;
				}
				else if (grid[i][j] == 0 && sum == 3) {					//life condition
					nextGen[i][j] = 1;
				}

			}
		}

		//move the nextgen values into the display grid
		for (int i = 0; i < width / resolution; i++) {
			for (int j = 0; j < height / resolution; j++) {
				grid[i][j] = nextGen[i][j];
			}
		}
		cout << "Generation " << count << endl;

		//DISPLAY BLOCK
		window.clear();
		for (int i = 0; i < width/resolution; i++) {
			for (int j = 0; j < height/resolution; j++) {
				if (grid[i][j] == 1) {
					RectangleShape organism(Vector2f(resolution, resolution));
					//organism.setFillColor(Color(128, cos(i * 2) * 255, 200));     //purple waves
					organism.setFillColor(Color(cos(i * (3.14159 / 32)) * 255, 40 , 255));		//purple waves v2
					//organism.setFillColor(Color(40, 255, cos(i * (3.14159/32)) * 60));
					organism.setOutlineThickness(1);
					organism.setOutlineColor(Color(0, 0, 0));
					organism.setPosition(j*resolution, i*resolution);
					window.draw(organism);
				}
			}
		}
		//draw objects

		//use to increment the gen by 1
		//system("pause");

		window.display();
		count++;
	}
	return 0;
}
