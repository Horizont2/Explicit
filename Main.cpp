#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Reservoir {
    string name;
    double width, length, maxDepth;

public:
    Reservoir() : name("Unknown"), width(0), length(0), maxDepth(0) {}
    Reservoir(const string& name, double w, double l, double d) : name(name), width(w), length(l), maxDepth(d) {}
    Reservoir(const Reservoir& other) = default;
    ~Reservoir() = default;

    double calculateVolume() const { return width * length * maxDepth; }
    double calculateSurfaceArea() const { return width * length; }
    bool isSameType(const Reservoir& other) const { return name == other.name; }
    bool compareSurfaceArea(const Reservoir& other) const { return calculateSurfaceArea() > other.calculateSurfaceArea(); }

    Reservoir& operator=(const Reservoir& other) = default;

    void setName(const string& n) { name = n; }
    string getName() const { return name; }
    void setWidth(double w) { width = w; }
    double getWidth() const { return width; }
    void setLength(double l) { length = l; }
    double getLength() const { return length; }
    void setMaxDepth(double d) { maxDepth = d; }
    double getMaxDepth() const { return maxDepth; }
};

class ReservoirManager {
    vector<Reservoir> reservoirs;

public:
    void addReservoir(const Reservoir& r) { reservoirs.push_back(r); }
    void removeReservoir(int index) {
        if (index >= 0 && index < reservoirs.size())
            reservoirs.erase(reservoirs.begin() + index);
    }

    void saveToFile(const string& filename) {
        ofstream file(filename);
        for (const auto& r : reservoirs) {
            file << "Name: " << r.getName() << "\n"
                 << "Width: " << r.getWidth() << "\n"
                 << "Length: " << r.getLength() << "\n"
                 << "Max Depth: " << r.getMaxDepth() << "\n"
                 << "Volume: " << r.calculateVolume() << "\n\n";
        }
    }

    void loadFromBinaryFile(const string& filename) {
        ifstream file(filename, ios::binary);
        reservoirs.clear();
        while (file.peek() != EOF) {
            string name;
            double width, length, maxDepth;
            file >> name >> width >> length >> maxDepth;
            reservoirs.push_back(Reservoir(name, width, length, maxDepth));
        }
    }
};

int main() {
    ReservoirManager manager;
    manager.addReservoir(Reservoir("Lake", 100, 200, 50));
    manager.addReservoir(Reservoir("Sea", 500, 1000, 200));
    manager.saveToFile("reservoirs.txt");
    return 0;
}
