#include "DigitalCounter.h"
#include "Stopwatch.h"
#include "Result.h"
#include <sstream>
#include <fstream>
#include <stdexcept>

Result result{};
Stopwatch stopwatch{};

DigitalCounter* res = nullptr;

void readFromConsole()
{
    std::cout << "\n\n *-------------------- At this stage, you need to define the stopwatch readings -------------------*\n";
    std::cout << " *--------------- Decide on the start of the countdown and the end of the stopwatch ---------------*\n\n";

    while (true)
    {
        double min = 0, max = 0;
        std::string input;
        std::string name;

        bool validName = false;
        bool validTime = false;

        while (!validName) 
        {
            std::cout << " Enter participant's name: ";
            std::getline(std::cin, name);

            // Check for the correctness of entering the name
            bool letters = false;
            for (char c : name) 
            {
                if (!std::isalpha(c)) 
                {
                    letters = true;
                    break;
                }
            }

            if (name.empty() || name.size() < 3 || name.find(' ') != std::string::npos || letters) 
            {
                std::cout << " Invalid input. Name must contain at least 3 letters, have no spaces, and consist only of letters!\n";
            }
            else 
            {
                validName = true;
            }
        }

        while (!validTime)
        {
            std::cout << " Enter the minimum time of the stopwatch: ";
            std::getline(std::cin, input);

            // Checking the correctness of entering the minimum time
            bool validInput = !input.empty() && std::all_of(input.begin(), input.end(), [](char c)
                {
                    return std::isdigit(c) || c == '.';
                });

            if (!validInput)
            {
                std::cout << " Invalid input. Enter only real numbers!\n";
            }
            else
            {
                min = std::stod(input);

                std::cout << " Enter the maximum time of the stopwatch: ";
                std::getline(std::cin, input);

                // Checking the correctness of entering the maximum time
                validInput = !input.empty() && std::all_of(input.begin(), input.end(), [](char c)
                    {
                        return std::isdigit(c) || c == '.';
                    });

                if (!validInput)
                {
                    std::cout << " Invalid input. Enter only real numbers!\n";
                }
                else
                {
                    max = std::stod(input);

                    if (min >= max)
                    {
                        std::cout << " Invalid input. Start time should be less than end time!\n";
                    }
                    else
                    {
                        validTime = true;
                    }
                }
            }
        }

        // Create, start, and stop the Stopwatch object
        auto sv = Stopwatch(name, min, max);
        sv.start();
        sv.stop(max);

        // Assign the address of the Stopwatch object to the res pointer and add the result to Result
        res = &sv;
        if (dynamic_cast<Stopwatch*>(res) != nullptr)
        {
            result.addRes(*dynamic_cast<Stopwatch*>(res));
        }

        std::cout << "\n Participant's data successfully recorded :)\n\n";

        std::cout << " *------------------- Do you want to continue or change data? -------------------*\n";
        std::cout << " *------------- If yes - enter 'y' or 'Y', if not - enter any key! --------------*\t";

        std::getline(std::cin, input);
        if (input != "y" && input != "Y") 
        {
            break;
        }
    }
}

void readFromFile(const std::string& filename) 
{
    std::ifstream in(filename);
    if (!in.is_open()) 
    {
        throw std::runtime_error(" Error opening file: " + filename);
    }
    else
    {
        std::string name;
        double min, max;
        while (in >> name >> min >> max)
        {
            auto sv = Stopwatch(name, min, max);
            sv.start();
            sv.stop(max);

            res = &sv;
            if (dynamic_cast<Stopwatch*>(res) != nullptr)
            {
                result.addRes(*dynamic_cast<Stopwatch*>(res));
            }
        }
        std::cout << " The file was successfully read and closed :)\n\n";
        in.close();
    }
}

void printResults()
{
    try
    {
        std::cout << "\n\n *------------- At this stage, you see the race results for one or more participants -------------*\n\n";

        auto allResults = result.getResults();
        Stopwatch minTime = result.getMinTime();
        Stopwatch maxTime = result.getMaxTime();

        for (const auto& stopwatch : allResults)
        {
            std::cout << " Participant's name: " << stopwatch.getName() << std::endl;
            std::cout << " Minimum race time: " << stopwatch.getMinimum() << " seconds\n";
            std::cout << " Maximum race time: " << stopwatch.getMaximum() << " seconds\n\n";
        }

        std::cout << "\n Minimum race time: " << minTime.getMinimum() << " seconds" << ", runner: " << minTime.getName() << std::endl;
        std::cout << " Maximum race time: " << maxTime.getMaximum() << " seconds" << ", runner: " << maxTime.getName() << std::endl;

        if (allResults.size() >= 2)
        {
            std::cout << "\n Average race time for all participants: " << result.getAvgTime() << " seconds\n";
        }
        else
        {
            std::cout << "\n In order to calculate the average time of the participants' race, there must be two or more of them!\n\n";
        }

        if (allResults.size() >= 4)
        {
            std::cout << "\n The results of the 3 winners: \n";
            for (auto time : result.getBestOf3())
            {
                std::cout << " Runner: " << time.getName() << " has best a time of race: " << time.getMinimum() << " seconds\n";
            }
            std::cout << "\n\n";
        }
        else
        {
            std::cout << " To determine the three winners of the competition, there must be four or more applicants!\n\n";
        }
    }
    catch (const std::exception& e)
    {
        std::cout << " Error: " << e.what() << std::endl;
    }
}

void writeToFile(const std::string& filename) 
{
    std::ofstream out(filename);
    if (!out.is_open()) 
    {
        throw std::runtime_error(" ,Error opening file: " + filename);
    }  
    else
    {
        auto allResults = result.getResults();
        Stopwatch minTime = result.getMinTime();
        Stopwatch maxTime = result.getMaxTime();

        for (const auto& stopwatch : allResults)
        {
            out << " Participant's name: " << stopwatch.getName() << std::endl;
            out << " Minimum race time: " << stopwatch.getMinimum() << " seconds\n";
            out << " Maximum race time: " << stopwatch.getMaximum() << " seconds\n";
        }

        out << "\n Minimum race time: " << minTime.getMinimum() << " seconds" << ", runner: " << minTime.getName() << std::endl;
        out << " Maximum race time: " << maxTime.getMaximum() << " seconds" << ", runner: " << maxTime.getName() << std::endl;

        if (allResults.size() >= 2)
        {
            out << "\n Average race time for all participants: " << result.getAvgTime() << " seconds\n";
        }
        else
        {
            out << "\n In order to calculate the average time of the participants' race, there must be two or more of them!\n\n";
        }

        if (allResults.size() >= 4)
        {
            out << "\n The results of the 3 winners: \n";
            for (auto time : result.getBestOf3())
            {
                out << " Runner: " << time.getName() << " has a best time of race: " << time.getMinimum() << " seconds\n";
            }
            out << "\n\n";
        }
        else
        {
            out << " To determine the three winners of the competition, there must be four or more applicants!\n\n";
        }
        std::cout << " The file was successfully completed and closed :)\n\n";
        out.close();
    }
}

void demonstrateConstructors() 
{
    std::cout << "\n *----------------- At this stage, you can see a demonstration of the constructors ------------------*\n\n";

    DigitalCounter counter1;
    std::cout << " Default constructor: Minimum race time = " << counter1.getMinimum() << "sec, Maximum race time = " << counter1.getMaximum() << "sec\n";

    DigitalCounter counter2(15.5, 18.7);
    std::cout << " Constructor with parameters : Minimum race time = " << counter2.getMinimum() << "sec, Maximum race time = " << counter2.getMaximum() << "sec\n";

    DigitalCounter counter3(counter2);
    std::cout << " Copy constructor: Minimum race time = " << counter3.getMinimum() << "sec, Maximum race time = " << counter3.getMaximum() << "sec\n";

    DigitalCounter counter4(std::move(counter1));
    std::cout << " Move constructor: Minimum race time = " << counter4.getMinimum() << "sec, Maximum race time = " << counter4.getMaximum() << "sec\n\n";
}

void demonstrateOperators()
{
    std::cout << "\n *--------- At this stage, you can see the change of race result for the disputed participant ---------*\n\n";

    DigitalCounter counter(8.4, 12.6);
    std::cout << " One of the participants has the following results: minimum = " << counter.getMinimum() << "sec and maximum: " << counter.getMaximum() << "sec time of the sprinter's race!\n";
    std::cout << " The judges wanted to choose the winner because he has the best minimum race time = " << counter.getMinimum() << " seconds!\n";
    std::cout << " But then it turned out that he started faster and 1 second was added to him, now his race time = " << (++counter).getValue() << " seconds!\n";
    std::cout << " He didn't like it and appealed, where he won himself 1 second, now it's his time again = " << (counter--).getValue() << " seconds!\n";
    std::cout << " But after the competition, organizers rewatched video and noticed delay, so added 3 seconds to the sprinter!\n";
    std::cout << " It's final result = " << (counter += 2).getValue() << " seconds, due to which the sprinter took one of the last places!\n\n";
}

int main()
{
    std::cout << "\n *----------------------- Results of the International Athletics Competitions ----------------------*\n\n";

    bool invalidChoice = false;

    while (!invalidChoice)
    {
        try
        {
            std::cout << "\n Select the source of the input data or other events:\n\n";
            std::cout << " 1) Manual input (must enter data from the console)\n";
            std::cout << " 2) Data from file (data is read from the input file)\n";
            std::cout << " 3) Demonstration all constructors\n";
            std::cout << " 4) Demonstration of operators overloading\n";
            std::cout << " 5) Close program (Enter)\n\n";
            std::cout << " Input your operation: ";

            std::string input;
            std::getline(std::cin, input);

            // Check input for a number
            bool isDigit = true;
            for (char c : input)
            {
                if (!std::isdigit(c))
                {
                    isDigit = false;
                    break;
                }
            }

            if (!isDigit)
            {
                std::cout << " Invalid input. Please enter a number!\n\n";
                continue;
            }

            int choice1 = std::stoi(input);

            switch (choice1)
            {
            case 1:
            {
                std::cout << " Selected option 1: Manual input\n";
                readFromConsole();
                break;
            }
            case 2:
            {
                std::cout << " Selected option 2: Data from file\n";
                readFromFile("inFile.txt");
                break;
            }
            case 3:
            {
                std::cout << " Selected option 3: Demonstration all constructors\n";
                demonstrateConstructors();
                continue;
            }
            case 4:
            {
                std::cout << " Selected option 4: Demonstration of operators overloading\n";
                demonstrateOperators();
                continue;
            }
            case 5:
            {
                std::cout << " Selected option 5: Close program\n";
                std::cout << "\n Thank you for your visit. Goodbye :)\n\n";
                return 1;
            }
            default:
                std::cout << " Invalid choice. Please enter a valid option!\n\n";
                continue;
            }
  
            std::cout << " Select the source of the output data:\n\n";
            std::cout << " 1) To the console\n";
            std::cout << " 2) To a file\n";
            std::cout << " 3) Close program\n\n";
            std::cout << " Input your operation: ";

            std::getline(std::cin, input);

            for (char c : input)
            {
                if (!std::isdigit(c))
                {
                    isDigit = false;
                    break;
                }
            }

            if (!isDigit)
            {
                std::cout << " Invalid input. Please enter a number!\n\n";
                continue;
            }

            int choice2 = std::stoi(input);

            switch (choice2)
            {
            case 1:
            {
                std::cout << " Selected option 1: Output to the console\n";
                printResults();
                break;
            }
            case 2:
            {
                std::cout << " Selected option 2: Output to file";
                writeToFile("outFile.txt");
                break;
            }
            case 3:
            {
                std::cout << " Selected option 3: Close program\n";
                std::cout << "\n Thank you for your visit. Goodbye :)\n\n";
                return 1;
            }
            default:
                std::cout << " Invalid choice. Please enter a valid option!\n\n";
                continue;
            }
        }
        catch (const std::exception& e)
        {
            std::cout << " Error: " << e.what() << std::endl;
            return 1;
        }
    }

    return 0;
}
