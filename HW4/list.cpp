void listAll(const MenuItem* m, string path) // two-parameter overload
{
    if (path != "")
        path += '/';

    path += m->name();

    cout << path << endl;

    if (m->menuItems() == nullptr)
        return;

    for (vector<MenuItem*>::const_iterator it = m->menuItems()->begin(); it != m->menuItems()->end(); it++)
    {
        listAll(*it, path);
    }
}