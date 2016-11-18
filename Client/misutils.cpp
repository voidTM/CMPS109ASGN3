

map<string,Identifier*> identifiers; // a map of all the existing identifiers (a.k.a variables)
map<string,Identifier*> typeSet; // a map of identifiers' prototypes that are used for cloning
//map<string,Instruction*> instSet; // a map of instructions' prototypes that are used for cloning
map<string,int> labels; // a map of defined labels
