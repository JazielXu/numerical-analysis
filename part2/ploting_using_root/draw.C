#include <iostream>
using namespace std;
int draw(){
	TCanvas *c=new TCanvas();
    c->SetFillColor(0);
    c1->GetFrame()->SetFillColor(20);
    c1->GetFrame()->SetBorderSize(12);
    
    TGraph graph("./08.txt","%lg %lg");
	graph.SetLineColor(2);
    graph.SetMarkerColor(2);
    graph.SetFillColor(0);
TGraph graph1("./10.txt","%lg %lg");
    
	graph1.SetLineColor(3);
    graph1.SetMarkerColor(3);
    graph1.SetFillColor(0);

TGraph graph2("./12.txt","%lg %lg");
    
	graph2.SetLineColor(4);
    graph2.SetMarkerColor(4);
    graph2.SetFillColor(0);

TGraph graph3("./14.txt","%lg %lg");
    
	graph3.SetLineColor(1);
    graph3.SetMarkerColor(1);
    graph3.SetFillColor(0);
TGraph graph4("./16.txt","%lg %lg");
    
	graph4.SetLineColor(6);
    graph4.SetMarkerColor(6);
    graph4.SetFillColor(0);
TMultiGraph *mg= new TMultiGraph();
mg->Add(&graph,"lp");graph.SetTitle("(0.8,0.8)");
mg->Add(&graph1,"lp");graph1.SetTitle("(1.0,1.0)");
mg->Add(&graph2,"lp");graph1.SetTitle("(1.2,1.2)");
mg->Add(&graph3,"lp");graph1.SetTitle("(1.4,1.4)");
mg->Add(&graph4,"lp");graph1.SetTitle("(1.6,1.6)");
mg->DrawClone("AC");

TLegend leg(.1,.7,.2,.75,"","NDC");
    leg.SetFillColor(0);

    leg.AddEntry(&graph,"(0.8,0.8)");
    
    leg.AddEntry(&graph1,"(1.0,1.0)");
leg.AddEntry(&graph2,"(1.2,1.2)");
leg.AddEntry(&graph3,"(1.4,1.4)");
leg.AddEntry(&graph4,"(1.6,1.6)");

    
    leg.DrawClone();

	return 0;
}
