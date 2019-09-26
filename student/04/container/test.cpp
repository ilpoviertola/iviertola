void read_integers(std::vector< int >& ints, int count)
{
    int new_integer = 0;
    for(int i = 0; i < count; ++i)
    {
        std::cin >> new_integer;
        ints.push_back(new_integer);
    }
}

bool same_values(std::vector< int >& ints)
{
    bool error;
    for(long unsigned int i = 0;i < ints.size() - 1;++i){
        if(ints.at(i) != ints.at(i+1)){
            error = true;
            break;
        }
    }
    if(error){return false;}else{return true;}
}

bool is_ordered_non_strict_ascending(std::vector< int >& ints)
{
    bool error;
    for(long unsigned int i = 0;i < ints.size() - 1;++i){
        if(ints.at(i) > ints.at(i+1)){
            error = true;
            break;
        }
    }
    if(error){return false;}else{return true;}
}

bool is_arithmetic_series(std::vector< int >& ints)
{
    bool error;
    for(long unsigned int i = 0;i < ints.size() - 2;++i){
        if(ints.at(i) - ints.at(i+1) != ints.at(i+1) - ints.at(i+2)){
            error = true;
            break;
        }
    }
    if(error){return false;}else{return true;}
}

bool is_geometric_series(std::vector< int >& ints)
{
    bool error;
    for(long unsigned int i = 0;i < ints.size() - 2;++i){
        if(ints.at(i) / ints.at(i+1) != ints.at(i+1) / ints.at(i+2)){
            error = true;
            break;
        }
    }
    if(error){return false;}else{return true;}
}
