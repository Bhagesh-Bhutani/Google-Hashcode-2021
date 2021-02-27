#include<bits/stdc++.h>
#define ll long long int
#define ld long double
using namespace std;

class street{
    public:
    ll B;
    ll E;
    string name;
    ll idx;
    ll L;
};

class car{
    public:
    ll P;
    vector<ll> *path = NULL;
};

class myPair{
    public:
    string name;
    ll T;
};

class output{
    public:
    ll i;
    ll Ei;
    vector<myPair> *names = NULL;
};

class spair{
    public:
    ll st_idx;
    ll count = 0;
};

bool comparator(spair &s1, spair &s2){
    return s1.count > s2.count;
}

bool myPair_comp(myPair &p1, myPair &p2){
    return p1.T > p2.T;
}

class vertex{
    public:
    ll i; // id of intersection vertex
    unordered_set<ll> *incoming_streets = NULL;
    unordered_set<ll> *outgoing_streets = NULL;
};

int main(){
    // ***** INPUT CODE ***** //
    fstream fin;
    fin.open("f.txt");
    string line;
    getline(fin,line);
    string s;
    stringstream ss(line);
    vector<string> first_line;
    while(getline(ss,s,' ')){
        first_line.push_back(s);
    }
    ll D = stoll(first_line.at(0));
    ll I = stoll(first_line.at(1));
    ll S = stoll(first_line.at(2));
    ll V = stoll(first_line.at(3));
    ll F = stoll(first_line.at(4));

    vector<unordered_set<ll>*> *all_inter_incoming = new vector<unordered_set<ll>*>();
    vector<spair> greedy_streets;
    for(ll i=0;i<I;i++){
        unordered_set<ll> *myset = new unordered_set<ll>();
        all_inter_incoming->push_back(myset);
    }

    unordered_map<string,ll> street_to_idx;
    unordered_map<ll,string> idx_to_street;
    ll street_idx = 0;
    vector<street> streets;
    for(ll i=0;i<S;i++){
        street st;
        string line;
        getline(fin,line);
        stringstream ss(line);
        string s;
        vector<string> inputs;
        while(getline(ss,s,' ')){
            inputs.push_back(s);
        }
        st.B = stoll(inputs.at(0));
        st.E = stoll(inputs.at(1));
        st.name = inputs.at(2);
        street_to_idx[st.name] = street_idx;
        idx_to_street[street_idx] = st.name;
        st.idx = street_to_idx.at(st.name);
        all_inter_incoming->at(st.E)->insert(street_idx);
        spair sp;
        sp.st_idx = street_idx;
        sp.count = 0;
        greedy_streets.push_back(sp);
        // cout<<"inserting "<<st.name<<" to : "<<st.E<<"\n";
        street_idx++;
        st.L = stoll(inputs.at(3));
        streets.push_back(st);
    }

    vector<car> cars;
    for(ll i=0;i<V;i++){
        car mycar;
        vector<ll> *path = new vector<ll>();
        string line;
        getline(fin,line);
        stringstream ss(line);
        string s;
        vector<string> inputs;
        while(getline(ss,s,' ')){
            inputs.push_back(s);
        }

        ll P = stoll(inputs.at(0));
        for(ll j=0;j<P;j++){
            string str = inputs.at(j+1);
            path->push_back(street_to_idx.at(str));
            ll myidx = street_to_idx.at(str);
            greedy_streets.at(myidx).count += 1;
        }
        mycar.P = P;
        mycar.path = path;
        cars.push_back(mycar);
    }

    sort(greedy_streets.begin() , greedy_streets.end() , comparator);
    unordered_set<ll> relevant;
    for(spair sp : greedy_streets){
        if(sp.count < 3){
            break;
        }
        relevant.insert(sp.st_idx);
    }

    // for(street st : streets){
    //     cout<<st.name<<" "<<st.idx<<"\n";
    // }

    // for(car c : cars){
    //     cout<<c.P<<"\n";
    // }

    fin.close();
    // ***** INPUT CODE END ***** //


    // ***** ALGORITHM START ***** //

    ll A = I; // number of intersections to specify the schedule for output file
    vector<output> ans;
    for(ll i=0;i<all_inter_incoming->size();i++){
        unordered_set<ll> *inc = all_inter_incoming->at(i);

        output myout;
        myout.i = i;
        // myout.Ei = inc->size();
        ll my_count = 0;
        vector<myPair> *temp = new vector<myPair>();
        for(auto it=inc->begin();it!=inc->end();it++){
            myPair mp;
            ll ele = (*it);
            // cout<<ele<<" ";
            mp.name = idx_to_street.at(ele);
            // mp.T = 1;
            if(relevant.count(ele) > 0){
                mp.T = 1;
                temp->push_back(mp);
                my_count++;
            } else {
                if(my_count == 0){
                    mp.T = 1;
                    temp->push_back(mp);
                    my_count++;
                } else{
                    continue;
                }
                
            }
            
            // count++;
        }
        myout.Ei = temp->size();
        // cout<<"\n";
        sort(temp->begin() , temp->end() , myPair_comp);
        myout.names = temp;
        ans.push_back(myout);
        cout<<"inter "<<i<<" done\n";
    }

    // ***** ALGORITHM END ***** //


    // ***** OUTPUT CODE START ***** //

    
    fstream fout;
    fout.open("o6.txt" , ios::out);
    fout<<A<<"\n";

    for(auto it = ans.begin();it!=ans.end();it++){
        fout<<it->i<<"\n";
        fout<<it->Ei<<"\n";
        for(int j=0;j<it->names->size();j++){
            myPair p = it->names->at(j);
            fout<<p.name<<" ";
            fout<<p.T<<"\n";
        }
    }

    fout.close();
    return 0;
}