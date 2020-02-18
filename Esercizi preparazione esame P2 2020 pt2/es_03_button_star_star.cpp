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