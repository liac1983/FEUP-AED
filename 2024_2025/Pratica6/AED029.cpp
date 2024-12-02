#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

struct Point {
    int x, y;
};

// Global pivot point for sorting
Point p1;

// Function to determine if three points make a left turn
bool left_turn(Point &p0, Point &p1, Point &p2) {
    int x0 = p0.x, x1 = p1.x, x2 = p2.x;
    int y0 = p0.y, y1 = p1.y, y2 = p2.y;
    // Calcula o determinante para verificar a orientação
    return (x1 - x0) * (y2 - y0) - (x2 - x0) * (y1 - y0) > 0;
}

// Comparator to sort by polar angle with respect to p1
bool compPolar(Point &p, Point &q) {
    return left_turn(p1, p, q);
}

// Function to find the bottom-most point
// Função para encontrar o ponto mais inferior (ou mais à esquerda em caso de empate)
int bottomVertex(vector<Point> &pts) {
    int bottom = 0; // Assume inicialmente que o primeiro ponto é o mais inferior
    for (int i = 1; i < (int)pts.size(); i++) {
        // Verifica se o ponto atual é mais baixo ou, em caso de empate, mais à esquerda
        if (pts[i].y < pts[bottom].y || (pts[i].y == pts[bottom].y && pts[i].x < pts[bottom].x)) {
            bottom = i;
        }
    }
    return bottom;
}
// anti-horária
// Output the points in the convex hull in counterclockwise order
void output(stack<Point> &s) {
    vector<Point> result;
    while (!s.empty()) {
        result.push_back(s.top()); // Transfere os pontos da pilha para o vetor
        s.pop();
    }
    reverse(result.begin(), result.end()); // Reverte a ordem para garantir saída anti-horária
    cout << result.size() << endl; // Exibe o número de pontos no casco convexo

    for (const auto &p : result) {
        cout << p.x << " " << p.y << endl; // Exibe as coordenadas de cada ponto
    }
}

// Graham Scan algorithm for convex hull
void GrahamScan(vector<Point> &pts) {
    int bottom = bottomVertex(pts);  // Encontra o ponto mais inferior
    swap(pts[0], pts[bottom]); // Coloca o ponto mais inferior na primeira posição
    p1 = pts[0]; // Define p1 como o pivô para ordenação

    // Sort the points by polar angle with respect to p1
    sort(pts.begin() + 1, pts.end(), compPolar);

    stack<Point> s; // Pilha para armazenar os pontos do casco convexo
    s.push(pts[0]); // Adiciona o ponto mais inferior
    s.push(pts[1]); // Adiciona o segundo ponto (após ordenação)

    // Process remaining points
    for (int i = 2; i < (int)pts.size(); i++) {
        Point top = s.top(); // Recupera o ponto no topo da pilha
        s.pop(); // Remove o ponto do topo para verificar a orientação
        // Remove pontos que não fazem uma "virada à esquerda"
        while (!s.empty() && !left_turn(s.top(), top, pts[i])) {
            top = s.top();
            s.pop();
        }
        s.push(top); // Adiciona de volta o último ponto válido
        s.push(pts[i]); // Adiciona o ponto atual ao casco
    }

    output(s); // Exibe os pontos do casco convexo
}

// Main function to read input and execute Graham Scan
int main() {
    int n;
    cin >> n;
    vector<Point> pts(n);

    for (int i = 0; i < n; i++) {
        cin >> pts[i].x >> pts[i].y;
    }

    GrahamScan(pts);

    return 0;
}
