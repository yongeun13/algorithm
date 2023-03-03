#include <iostream>
#include <vector>
#include <algorithm>
#define BIGNUM 987654321
using namespace std;
// collision find algorithm update
// do not using vector
// search all 2 atom collition


struct Coordinate {
    int x;
    int y;
    Coordinate operator+(Coordinate &p)
        {return {x + p.x, y + p.y};}
    bool operator<(Coordinate &p)
        {return x < p.x || (x == p.x && y < p.y);}
};

struct Atom {
    Coordinate p;
    int dir;
    int energy;
};

struct Collision {
    int a1;
    int a2;
    int c_time; // collision time
    bool operator<(Collision &c) {
        return c_time < c.c_time;
    }
};

vector<int> used; // used atom check

vector<Atom> atom = vector<Atom>();
vector<Collision> collision;

int main() {
    // read 1 int
    int T;
    cin >> T;
    // run testcase loop
    for(int testcase = 1; testcase <= T; ++testcase) {
        // read 1 int
        int N;
        cin >> N;
        // prepare used
        used = vector<int>(N, BIGNUM);
        // read N atom info
        atom.clear();
        for(int i = 0; i < N; ++i) {
            int x, y, dir, energy;
            cin >> x >> y >> dir >> energy;
            atom.push_back({{x, y}, dir, energy});
        }
        // calculate collision
        collision.clear();
        for(int i = 0; i < N; ++i) {
            for(int j = i + 1; j < N; ++j) {
                Atom *a1, *a2;
                int c_time = 0; // total diatance atoms moved
                if(atom[i].p < atom[j].p) {a1 = &atom[i]; a2 = &atom[j];} // make order of 2 atom
                else {a1 = &atom[j]; a2 = &atom[i];}
                if(a1->p.y == a2->p.y && a1->dir == 3 && a2->dir == 2) // x axis
                    c_time = a2->p.x - a1->p.x;
                else if(a1->p.x == a2->p.x && a1->dir == 0 && a2->dir == 1) // y axis
                    c_time = a2->p.y - a1->p.y;
                else if(a1->p.x - a2->p.x == a1->p.y - a2->p.y && (a1->dir == 0 && a2->dir == 2 || a1->dir == 3 && a2->dir == 1)) // y=x axis, up, down
                    c_time = (a2->p.x - a1->p.x) << 1;
                else if(a1->p.x - a2->p.x == a2->p.y - a1->p.y && (a1->dir == 3 && a2->dir == 0 || a1->dir == 1 && a2->dir == 2)) // y=-x axis, up, down
                    c_time = (a2->p.x - a1->p.x) << 1;
                else // do not collide
                    continue;
                collision.push_back({i, j, c_time});
            }
        }
        // process collision
        int total_energy = 0;
        sort(collision.begin(), collision.end());
        vector<Collision>::iterator it = collision.begin();
        vector<Collision>::iterator it_end = collision.end();
        for(; it != it_end; ++it) {
            if(used[it->a1] < it->c_time || used[it->a2] < it->c_time) continue;
            if(used[it->a1] != it->c_time) total_energy += atom[it->a1].energy;
            if(used[it->a2] != it->c_time) total_energy += atom[it->a2].energy;
            used[it->a1] = it->c_time;
            used[it->a2] = it->c_time;
        }
        // print result
        cout << '#' << testcase << ' ' << total_energy << '\n';
    }
}