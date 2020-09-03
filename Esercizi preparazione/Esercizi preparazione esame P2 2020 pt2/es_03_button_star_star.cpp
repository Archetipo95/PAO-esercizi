Button** Fun(const Container& c) {
    vector<button*> aux;
    vector<Container*> cont;
    for(auto it = cont.begin(); it != cont.end(); ++it){
        Button* b = dynamic_cast<Button*>(*it);
        if(b){
            aux.push_back(b);
            MenuItem* m = dynamic_cast<MenuItem*>(*it);
            if(m && m->getContainers().size() > 1)
                m->setEnabled(false);
        }
    }
    if(aux.empty()) return nullptr;
    return &aux[0];
}

Button** Fun(const Container& c) {
    vector<Button*> v;
    for(auto* el : c.getComponents()){
        auto* b = dynamic_cast<Button*>(el);
        if(b){
            v.push_back(b);
            auto* m = dynamic_cast<MenuItem*>(el);
            if(m && m->getContainers().size()>1){
                m->setEnabled(false);
            }
        }
    }
    if(v.empty()) return nullptr;
    return &v[0];
}