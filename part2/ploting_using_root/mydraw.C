#include <iostream>
using namespace std;
int mydraw(){
	TCanvas *c=new TCanvas();
    c->SetFillColor(0);
    c1->GetFrame()->SetFillColor(20);
    c1->GetFrame()->SetBorderSize(12);

TGraph graph1("./drawin.txt","%lg %lg");
    
	graph1.SetLineColor(3);
    graph1.SetMarkerColor(3);
    graph1.SetFillColor(0);
graph1.DrawClone("AC");
return 0;
}
