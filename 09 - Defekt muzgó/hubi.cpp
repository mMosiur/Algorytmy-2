int main()
{
    std::ios::sync_with_stdio(false);
 
    Tree d_utworow;
    Tree d_zespolow;
    std::string operacji;
    std::getline(std::cin, operacji);
    int s;
    sscanf(operacji.c_str(), "%d", &s);
 
    for (int i = 0; i < s; i++)
    {
        solve(&d_zespolow, &d_utworow);
    }
    return 0;
}
 
 
 
void solve(Tree* drzewo_zespolow, Tree* drzewo_utworow)
{
    std::string temp_1, zespol, utwor;
    std::cin >> temp_1;
    std::cin.ignore();
    if (temp_1 == "d") // dodawanie
    {
        std::getline(std::cin, zespol);
        std::getline(std::cin, utwor);
 
        // dodaj zespol
        Node* node_zespol = drzewo_zespolow->insert(zespol);
        Node* node_utwor = drzewo_utworow->insert(utwor);
        // utworz polaczenia
        node_zespol->friend_list.push_back(node_utwor);
        node_utwor->friend_list.push_back(node_zespol);
    }
    else if (temp_1 == "z")
    {
        std::getline(std::cin, utwor);
        Node* s = drzewo_utworow->search(drzewo_utworow->root, utwor);
        if (s != nullptr && s->value == utwor)
        {
            for (auto a : s->friend_list)
                std::cout << a->value << "\n";
        }
 
    }
    else if (temp_1 == "w")
    {
        std::getline(std::cin, zespol);
        Node* s = drzewo_zespolow->search(drzewo_zespolow->root, zespol);
        if (s != nullptr && s->value == zespol)
        {
            for (auto a : s->friend_list)
                std::cout << a->value << "\n";
        }
 
    }
}