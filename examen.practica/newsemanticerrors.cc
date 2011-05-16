
void erroriteratorrequired(int l,string s) {
  TypeError = 1;
  cout<<"L. "<<l<<": "<<s<<" must be applied to an iterator."<<endl;
}

void errorrefiteratorrequired(int l,string s) {
  TypeError = 1;
  cout<<"L. "<<l<<": "<<s<<" must be applied to a referenceable iterator."<<endl;
}

void errorarrayrequired(int l,string s) {
  TypeError = 1;
  cout<<"L. "<<l<<": Referenceable array required in call to "<<s<<"()."<<endl;
}

void errorconstparam(int l) {
  TypeError = 1;
  cout<<"L. "<<l<<": Parameter is const and cannot be modified."<<endl;
}

