#include <iostream>
#include <fstream>
#include <string>


Double_t cooling(Double_t *x, Double_t *par)
{
  return par[0]+par[1]*x[0];
}

Double_t heating(Double_t *x, Double_t *par)
{
  return par[0]+par[1]*x[0];
}


void DHT22_INTT_module_001()
{
  std::ifstream file("DHT22_INTT_module_001.txt", std::ifstream::in);
  TString line;
  TGraph *g = new TGraph();
  TGraph *g1 = new TGraph();
  TGraph *g2 = new TGraph();
  TGraph *g3 = new TGraph();
  TGraph *l5 = new TGraph();
  TGraph *l6 = new TGraph();
  TGraph *l7 = new TGraph();
  TGraph *l8 = new TGraph();
  

  TString ymd, hms;
  Int_t lapse;
  Float_t temp, humid, dewpoint;
  Int_t hr, min, sec;
  while(file >> ymd >> hms >> lapse >> temp >> humid >> dewpoint)
    {
      //std::cout << "col1 : " << ymd << " col2 : " << hms << std::endl;
      //TDatime *t = new TDatime(ymd +" "+ hms);
      hr = lapse / 3600;
      min = (lapse % 3600) / 60;
      sec = (lapse % 3600) % 60;
      //td::cout << "time : " << hr << ":" << min << ":" << sec << endl;
      TDatime *t = new TDatime(2020, 8, 23, hr, min, sec);
      g->SetPoint(g->GetN(), t->Convert(), temp);
      g1->SetPoint(g1->GetN(), t->Convert(), humid);
      g2->SetPoint(g2->GetN(), t->Convert(), dewpoint);
      g3->SetPoint(g3->GetN(), t->Convert(), temp-dewpoint);
      l5->SetPoint(l5->GetN(), t->Convert(), 65.2);
      l6->SetPoint(l6->GetN(), t->Convert(), 26.6);
      l7->SetPoint(l7->GetN(), t->Convert(), 39.5);
      l8->SetPoint(l8->GetN(), t->Convert(), -9.8);
      
    }
  g->SetMarkerColor(kBlack);
  g->SetMarkerSize(0.6);
  g->SetMarkerStyle(20);
  g->SetLineWidth(0);
  g->SetTitle("Temperature");

  g1->SetMarkerColor(kOrange);
  g1->SetMarkerSize(0.6);
  g1->SetMarkerStyle(20);
  g1->SetLineWidth(0);
  g1->SetTitle("Humidity");

  g2->SetMarkerColor(kGreen+1);
  g2->SetMarkerSize(0.6);
  g2->SetMarkerStyle(20);
  g2->SetLineWidth(0);
  g2->SetTitle("Dew Point");

  g3->SetMarkerColor(kCyan-7);
  g3->SetMarkerSize(0.6);
  g3->SetMarkerStyle(20);
  g3->SetLineWidth(0);
  g3->SetTitle("#Delta Temperature");

  l5->SetLineColor(kAzure-3);
  l5->SetLineWidth(2);
  l5->SetMarkerColor(kAzure-3);
  l5->SetMarkerSize(0.2);
  l5->SetMarkerStyle(20);

  l6->SetLineColor(kAzure-3);
  l6->SetLineWidth(2);
  l6->SetMarkerColor(kAzure-3);
  l6->SetMarkerSize(0.2);
  l6->SetMarkerStyle(20);

  l7->SetLineColor(kAzure-3);
  l7->SetLineWidth(2);
  l7->SetMarkerColor(kAzure-3);
  l7->SetMarkerSize(0.2);
  l7->SetMarkerStyle(20);
  
  l8->SetLineColor(kAzure-3);
  l8->SetLineWidth(2);
  l8->SetMarkerColor(kAzure-3);
  l8->SetMarkerSize(0.2);
  l8->SetMarkerStyle(20);
  
  TGraph *l1 = new TGraph();
  TDatime *t1 = new TDatime(2020, 8, 23, 0, 17, 12);//1032
  for(int i=0; i<1210; i++)
    {
      l1->SetPoint(l1->GetN(), t1->Convert(), (i/10)-40);
    }
  //l1->SetMarkerColor(kRed);
  l1->SetLineColor(kAzure-3);
  l1->SetLineWidth(2);
  l1->SetMarkerColor(kAzure-3);
  l1->SetMarkerSize(0.2);
  l1->SetMarkerStyle(20);
  /*
  TGraph *l1 = new TGraph();
  TDatime *t1 = new TDatime(2020, 8, 23, 1, 43, 50);//6230
  for(int i=0; i<1210; i++)
    {
      l1->SetPoint(l1->GetN(), t1->Convert(), (i/10)-40);
    }
  //l1->SetMarkerColor(kRed);
  l1->SetLineColor(kAzure-3);
  l1->SetLineWidth(2);
  l1->SetMarkerColor(kAzure-3);
  l1->SetMarkerSize(0.2);
  l1->SetMarkerStyle(20);
  */

  TGraph *l2 = new TGraph();
  TDatime *t2 = new TDatime(2020, 8, 23, 1, 8, 8);//4088
  for(int i=0; i<1210; i++)
    {
      l2->SetPoint(l2->GetN(), t2->Convert(), (i/10)-40);
    }
  //l2->SetMarkerColor(kRed);
  l2->SetLineColor(kAzure-3);
  l2->SetLineWidth(2);
  l2->SetMarkerColor(kAzure-3);
  l2->SetMarkerSize(0.2);
  l2->SetMarkerStyle(20);

  /*
  // fit cooling rate
  Double_t p[4];
  TF1 *fit_cooling = new TF1("fit_cooling", "pol1(0)", t1->Convert(), t2->Convert());
  //fit_cooling->SetParameters(0, 25503000, 25643000);
  //fit_cooling->SetParameters(1, -0.006, -0.001);
  g->Fit("fit_cooling", "", "", t1->Convert(), t2->Convert());
  fit_cooling->SetParameter(0, 255798800);
  fit_cooling->SetParameter(1, -0.0161433);
  fit_cooling->SetTitle("Cooling fit");
  fit_cooling->SetLineWidth(3);
  */
  
  
  TGraph *l3 = new TGraph();
  TDatime *t3 = new TDatime(2020, 8, 23, 1, 16, 50);//4610
  for(int i=0; i<1210; i++)
    {
      l3->SetPoint(l3->GetN(), t3->Convert(), (i/10)-40);
    }
  //l2->SetMarkerColor(kRed);
  l3->SetLineColor(kAzure-3);
  l3->SetLineWidth(2);
  l3->SetMarkerColor(kAzure-3);
  l3->SetMarkerSize(0.2);
  l3->SetMarkerStyle(20);

  TGraph *l4 = new TGraph();
  TDatime *t4 = new TDatime(2020, 8, 23, 1, 35, 15);//5715
  for(int i=0; i<1210; i++)
    {
      l4->SetPoint(l4->GetN(), t4->Convert(), (i/10)-40);
    }
  //l2->SetMarkerColor(kRed);
  l4->SetLineColor(kAzure-3);
  l4->SetLineWidth(2);
  l4->SetMarkerColor(kAzure-3);
  l4->SetMarkerSize(0.2);
  l4->SetMarkerStyle(20);

  /*
  // fit heating rate
  TF1 *fit_heating = new TF1("fit_heating", "pol1(0)", t3->Convert(), t4->Convert()-100);
  //fit_heating->SetParameters(2, -69485500, -68485500);
  //fit_heating->SetParameters(3, 0.04, 0.045);
  //g->Fit("fit_heating", "", "", t3->Convert(), t4->Convert());
 
  fit_heating->SetParameter(0, -71695100);
  fit_heating->SetParameter(1, 0.043687);
  fit_heating->SetTitle("Heating fit");
  fit_heating->SetLineWidth(3);
  */
  
  TCanvas *c = new TCanvas("c", "", 1600, 1000);
  gStyle->SetOptTitle(1);
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);
  gStyle->SetLabelSize(0.025,"xy");
  gStyle->SetLabelFont(42,"xy");

  TMultiGraph *mg = new TMultiGraph();

  mg->Add(g, "P");
  mg->Add(g1, "LPY+");
  //mg->Add(g2, "P");
  //mg->Add(g3, "P");
  //mg->Add(l1, "PC");
  //mg->Add(l2, "PC");
  //mg->Add(l3, "PC");
  //mg->Add(l4, "PC");
  //mg->Add(l5, "PC");
  //mg->Add(l6, "PC");
  //mg->Add(l7, "PC");
  //mg->Add(l8, "PC");

  //mg->SetMarkerSize(5.0);
  mg->GetXaxis()->SetTimeDisplay(1);
  mg->GetXaxis()->SetTimeFormat("%Hhr%Mm");
  //mg->GetXaxis()->SetTimeFormat("#splitline{%Y-%m-%d}{%H:%M:%S}");
  //mg->GetXaxis()->SetTimeOffset(0,"gmt");
  mg->GetXaxis()->SetLabelOffset(0.025);

  TDatime *tmin = new TDatime(2020, 8, 23, 0, 0, 0);
  TDatime *tmax = new TDatime(2020, 8, 23, 16, 0, 0);
  mg->GetXaxis()->SetRangeUser(tmin->Convert(), tmax->Convert());
  mg->GetYaxis()->SetRangeUser(-40, 80);
  mg->GetYaxis()->SetTitle("#circC");
  mg->Draw("APL+");
  
  TGaxis *RYaxis = new TGaxis(1, 0, 1, 1, 0, 100, 510, "+L");
  RYaxis->SetName("RYaxis");
  RYaxis->Draw();
  std::cout << gPad->GetUxmin() << std::endl;
  std::cout << gPad->GetUxmax() << std::endl;
  
  //fit_cooling->Draw("SAME");
  //fit_heating->Draw("SAME");
  //c->BuildLegend(0.74, 0.15, 0.88, 0.25);

  TLegend *legend = new TLegend(0.65, 0.2, 0.85, 0.4);
  legend->SetBorderSize(0);
  legend->AddEntry(g, "#scale[0.6]{Temperature}", "P");
  //legend->AddEntry(g1, "#scale[0.9]{Humidity}", "P");
  //legend->AddEntry(g2, "#scale[0.8]{Dew Point}", "P");
  //legend->AddEntry(g3, "#scale[0.7]{Delta Temperature}", "P");
  legend->SetFillStyle(0);
  legend->Draw("SAME");
  
  TLatex *latex = new TLatex();
  TDatime *text = new TDatime(2020, 8, 23, 11, 30, 0);
  //TDatime *text1 = new TDatime(2020, 8, 23, 11, 0, 0);
  latex->DrawLatex(text->Convert(), -20, "#scale[0.4]{Cooling Rate = -0.968#circC/min}");
  //latex->DrawLatex(text->Convert(), -20, "#scale[0.4]{Heating Rate = 2.62#circC/min}");
  //latex->DrawLatex(text->Convert(), -24, "#scale[0.4]{Max Delta Temp = 65.2#circC}");
  //latex->DrawLatex(text->Convert(), -32, "#scale[0.4]{Min Delta Temp = 26.6#circC}");
  //latex->DrawLatex(text->Convert(), -24, "#scale[0.4]{Max Temp = 39.5#circC}");
  //latex->DrawLatex(text->Convert(), -32, "#scale[0.4]{Min Temp = -9.8#circC}");

  
}
