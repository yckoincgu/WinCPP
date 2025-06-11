#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <limits> // For numeric_limits

// Function to check if a point (x1, x2) satisfies all inequalities
bool isFeasible(double x1, double x2) {
    // (1) 2x₁ + x₂ ≤ 18
    if (2 * x1 + x2 > 18) {
        return false;
    }
    // (2) 2x₁ + 3x₂ ≤ 42
    if (2 * x1 + 3 * x2 > 42) {
        return false;
    }
    // (3) 3x₁ + x₂ ≤ 24
    if (3 * x1 + x2 > 24) {
        return false;
    }
    // (4) x₁ ≥ 0
    if (x1 < 0) {
        return false;
    }
    // (5) x₂ ≥ 0
    if (x2 < 0) {
        return false;
    }
    return true;
}

int main() {
    const double x1_min = 0.0;
    const double x1_max = 10.0; // Based on intercepts (max x1 intercept is 9, 8, 21)
    const double x2_min = 0.0;
    const double x2_max = 25.0; // Based on intercepts (max x2 intercept is 18, 14, 24)
    const double step = 0.05; // Granularity of the grid

    std::ofstream feasible_points_file("feasible_points.csv");
    if (!feasible_points_file.is_open()) {
        std::cerr << "Error: Could not open feasible_points.csv for writing.\n";
        return 1;
    }

    // Write header for CSV
    feasible_points_file << "x1,x2\n";

    // Generate points and check feasibility
    for (double x1 = x1_min; x1 <= x1_max; x1 += step) {
        for (double x2 = x2_min; x2 <= x2_max; x2 += step) {
            if (isFeasible(x1, x2)) {
                feasible_points_file << x1 << "," << x2 << "\n";
            }
        }
    }
    feasible_points_file.close();
    std::cout << "Feasible points saved to feasible_points.csv\n";

    // --- Generate Gnuplot script ---
    std::ofstream gnuplot_script_file("plot_script.gp");
    if (!gnuplot_script_file.is_open()) {
        std::cerr << "Error: Could not open plot_script.gp for writing.\n";
        return 1;
    }

    gnuplot_script_file << "set title 'Feasible Region of Linear Inequalities'\n";
    gnuplot_script_file << "set xlabel 'x1'\n";
    gnuplot_script_file << "set ylabel 'x2'\n";
    gnuplot_script_file << "set grid\n";
    gnuplot_script_file << "set xrange [0:" << x1_max + 1 << "]\n"; // Extend range slightly
    gnuplot_script_file << "set yrange [0:" << x2_max + 1 << "]\n"; // Extend range slightly
    gnuplot_script_file << "set key outside\n"; // Place legend outside plot area

    // Plot the lines
    // Line 1: 2x1 + x2 = 18  => x2 = 18 - 2x1
    gnuplot_script_file << "plot (18 - 2*x) title '2x1 + x2 = 18' lc rgb 'red' lw 2, \\\n";
    // Line 2: 2x1 + 3x2 = 42 => 3x2 = 42 - 2x1 => x2 = (42 - 2x1) / 3
    gnuplot_script_file << "     (42 - 2*x)/3 title '2x1 + 3x2 = 42' lc rgb 'blue' lw 2, \\\n";
    // Line 3: 3x1 + x2 = 24  => x2 = 24 - 3x1
    gnuplot_script_file << "     (24 - 3*x) title '3x1 + x2 = 24' lc rgb 'green' lw 2, \\\n";
    // Plot the feasible points as dots
    gnuplot_script_file << "     'feasible_points.csv' using 1:2 with dots title 'Feasible Region' lc rgb 'dark-grey'\n";

    gnuplot_script_file.close();
    std::cout << "Gnuplot script saved to plot_script.gp\n";
    std::cout << "\nTo view the diagram:\n";
    std::cout << "1. Make sure Gnuplot is installed on your system.\n";
    std::cout << "2. Open a terminal or command prompt in the directory where you ran this program.\n";
    std::cout << "3. Run Gnuplot with: gnuplot -persist plot_script.gp\n";
    std::cout << "   (The '-persist' option keeps the plot window open.)\n";
    std::cout << "   Alternatively, you can open Gnuplot and type: load 'plot_script.gp'\n";

    // For keeping the console open in some environments
    std::cout << "\nPress Enter to exit.";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();

    return 0;
}