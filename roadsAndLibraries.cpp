#include <bits/stdc++.h>

using namespace std;

map<int, int> p;
map<int, int> rnk;

vector<string> split_string(string);

void MAKE_SET(int x)
{
    p[x] = x;
    rnk[x] = 0;
}

int FIND_SET(int x)
{
    if (x != p[x])
        p[x] = FIND_SET(p[x]);
    return p[x];
}

void LINK(int x, int y)
{
    if (rnk[x] > rnk[y])
        p[y] = x;
    else
    {
        p[x] = y;
        if (rnk[x] == rnk[y])
            rnk[y] = rnk[y] + 1;
    }
}
void UNION(int x, int y)
{
    LINK(FIND_SET(x), FIND_SET(y));
}

int CONNECTED_COMPONENTS(vector<vector<int>> G, int n)
{
    int union_counter = 0;
    for (int x = 1; x <= n; x++)
        MAKE_SET(x);
    int u,v;
    for (int i = 0; i < G.size(); i++)
    {
        u = G[i][0];
        v = G[i][1];
        if ( FIND_SET(u) != FIND_SET(v) )
        {
            UNION(u, v);
            union_counter++;
        }
    }
    return union_counter;
}
// Complete the roadsAndLibraries function below.
//long MAKE-SET(long )
long roadsAndLibraries(int n, int c_lib, int c_road, vector<vector<int>> cities) 
{    
    int m = cities.size();
    int n_roads = 0;
    int uc = CONNECTED_COMPONENTS(cities, n);
    int k = n - uc;
    //cout << k << endl;
    if(c_lib <= c_road)
        return long(n) * long(c_lib);
    else
        if ( m < n-k )
            n_roads = m;
        else
            n_roads = n-k;
        return (long(n_roads) * long(c_road))  + (long(k) * long(c_lib));
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string nmC_libC_road_temp;
        getline(cin, nmC_libC_road_temp);

        vector<string> nmC_libC_road = split_string(nmC_libC_road_temp);

        int n = stoi(nmC_libC_road[0]);

        int m = stoi(nmC_libC_road[1]);

        int c_lib = stoi(nmC_libC_road[2]);

        int c_road = stoi(nmC_libC_road[3]);

        vector<vector<int>> cities(m);
        for (int i = 0; i < m; i++) {
            cities[i].resize(2);

            for (int j = 0; j < 2; j++) {
                cin >> cities[i][j];
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        long result = roadsAndLibraries(n, c_lib, c_road, cities);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
