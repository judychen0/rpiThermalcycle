#include <iostream>
#include <fstream>
#include <string>
#define ncolor 7


Double_t cooling(Double_t *x, Double_t *par)
{
  return par[0]+par[1]*x[0];
}

Double_t heating(Double_t *x, Double_t *par)
{
  return par[0]+par[1]*x[0];
}


void DHT22_pt100_pt1000()
{
  /// 1st part -- save TGraphs from data.txt
  
  std::ifstream file("../textfile/HGCAL_30cycle_data.txt", std::ifstream::in);

  Int_t lapse;
  Float_t temp_DHT, humid_DHT, dewpoint_DHT;
  Float_t temp_pt100, temp_pt1000;
  Float_t temp_hitachi, humid_hitachi;
  Int_t hr, min, sec;

  TGraph *g0 = new TGraph();
  TGraph *g1 = new TGraph();
  TGraph *g2 = new TGraph();
  TGraph *g3 = new TGraph();
  TGraph *g4 = new TGraph();
  TGraph *g5 = new TGraph();
  TGraph *g6 = new TGraph();

  while(file >> lapse >> temp_DHT >> humid_DHT >> dewpoint_DHT >> temp_pt100 >> temp_pt1000 >> temp_hitachi >> humid_hitachi)
  //while(file >> lapse >> temp_DHT >> humid_DHT >> dewpoint_DHT >> temp_pt100 >> temp_hitachi >> humid_hitachi)
    {
      hr = lapse / 3600;
      min = (lapse % 3600) / 60;
      sec = (lapse % 3600) % 60;

      TDatime *t = new TDatime(2021, 8, 31, hr, min, sec);
      g0->SetPoint(g0->GetN(), t->Convert(), temp_DHT);
      g1->SetPoint(g1->GetN(), t->Convert(), humid_DHT);
      g2->SetPoint(g2->GetN(), t->Convert(), dewpoint_DHT);
      g3->SetPoint(g3->GetN(), t->Convert(), temp_pt100);
      g4->SetPoint(g4->GetN(), t->Convert(), temp_pt1000);
      g5->SetPoint(g5->GetN(), t->Convert(), temp_hitachi);
      g6->SetPoint(g6->GetN(), t->Convert(), humid_hitachi);
    }
  

  //string hexcolor[ncolor] = {"#fff176", "#03a9f4", "#ff3360", "#b23b8c", "#96ff5a", "#a983d3", "#ff9e00", "#00FFFF", "#FFCCCC", "#3d5afe", "#67ccc1"};
  string hexcolor[ncolor] = {"#ff3360", "#67ccc1", "#fff176", "#96ff5a", "#03a9f4", "#3d5afe", "#ff9e00"};
  TColor *color[ncolor];
  Int_t cnum[ncolor];
   
  for(Int_t j=0; j<ncolor; j++){
    color[j] = new TColor();
    Int_t n = hexcolor[j].length();
    char chararray[n+1];
    strcpy(chararray, hexcolor[j].c_str());
    cnum[j] = color[j]->GetColor(chararray);
  }
  
  g0->SetMarkerColor(cnum[0]);
  g0->SetMarkerSize(0.6);
  g0->SetMarkerStyle(24);
  g0->SetLineWidth(0);
  g0->SetTitle("DHT Temperature");

  g1->SetMarkerColor(cnum[1]);
  g1->SetMarkerSize(0.6);
  g1->SetMarkerStyle(24);
  g1->SetLineWidth(0);
  g1->SetTitle("DHT Humidity");

  g2->SetMarkerColor(cnum[2]);
  g2->SetMarkerSize(0.6);
  g2->SetMarkerStyle(24);
  g2->SetLineWidth(0);
  g2->SetTitle("Dew point");

  g3->SetMarkerColor(cnum[3]);
  g3->SetMarkerSize(0.6);
  g3->SetMarkerStyle(24);
  g3->SetLineWidth(0);
  g3->SetTitle("pt100 Temperature");

  g4->SetMarkerColor(cnum[4]);
  g4->SetMarkerSize(0.6);
  g4->SetMarkerStyle(24);
  g4->SetLineWidth(0);
  g4->SetTitle("pt1000 Temperature");

  
  g5->SetMarkerColor(cnum[5]);
  g5->SetMarkerSize(0.6);
  g5->SetMarkerStyle(24);
  g5->SetLineWidth(0);
  g5->SetTitle("Hitachi Temperature");

  g6->SetMarkerColor(cnum[6]);
  g6->SetMarkerSize(0.6);
  g6->SetMarkerStyle(24);
  g6->SetLineWidth(0);
  g6->SetTitle("Hitachi Humidity");
  


  /// 2nd part -- fit graphs and plot TMultigraphs

  TCanvas *c1 = new TCanvas("c1", "c", 1600, 1000);
  gStyle->SetOptTitle(1);
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);
  gStyle->SetLabelSize(0.025,"xy");
  gStyle->SetLabelFont(42,"xy");
  TDatime *tmin = new TDatime(2021, 8, 30, 23, 0, 0);
  TDatime *tmax = new TDatime(2021, 9, 01, 10, 0, 0);

  TMultiGraph *mg_temp = new TMultiGraph();
  mg_temp->Add(g5, "P");
  mg_temp->Add(g2, "P");
  mg_temp->Add(g0, "P");
  //mg_temp->Add(g3, "P");
  mg_temp->Add(g4, "P");
  
  mg_temp->GetXaxis()->SetTimeDisplay(1);
  mg_temp->GetXaxis()->SetTimeFormat("%Hhr%Mm");
  mg_temp->GetXaxis()->SetLabelOffset(0.025);
  
  mg_temp->GetXaxis()->SetRangeUser(tmin->Convert(), tmax->Convert());
  mg_temp->GetYaxis()->SetRangeUser(-60, 40);//temp
  mg_temp->GetYaxis()->SetTitle("Temperature(#circC)");
  gPad->cd();
  mg_temp->Draw("AP");

  TLegend *legend = new TLegend(0.1, 0.78, 0.25, 0.9);
  legend->AddEntry(g0, "DHT Temperature", "P");
  legend->AddEntry(g2, "Dew point", "P");
  //legend->AddEntry(g3, "pt100 Temperature", "P");
  legend->AddEntry(g4, "pt1000 Temperature", "P");
  legend->AddEntry(g5, "Hitachi Temperature", "P");
  legend->Draw();
  c1->SaveAs(Form("../graph/%s_temp.png", "HGCAL_30cycle"));
  c1->SaveAs(Form("../graph/%s_temp.pdf", "HGCAL_30cycle"));

  Double_t xmin, ymin, xmax, ymax;
  gPad->GetRangeAxis(xmin, ymin, xmax, ymax);
  cout << "Axis range : " << xmin << ", " << ymin << ", " << xmax << ", " << ", " << ymax << endl;
  // TMultiGraph *mg_humid = new TMultiGraph();
  // mg_humid->Add(g1, "P");
  // mg_humid->Add(g6, "P");

  // mg_humid->GetXaxis()->SetTimeDisplay(1);
  // mg_humid->GetXaxis()->SetTimeFormat("%Hhr%Mm");
  // mg_humid->GetXaxis()->SetLabelOffset(0.025);

  // mg_humid->GetXaxis()->SetRangeUser(tmin->Convert(), tmax->Convert());
  // mg_humid->GetYaxis()->SetRangeUser(0, 80);//Humid
  // mg_humid->GetYaxis()->SetTitle("Humidity(%)");
  // mg_humid->Draw("APY+");

  // legend->Clear();
  // legend->AddEntry(g1, "DHT Humidity", "P");
  // legend->AddEntry(g6, "Hitachi Humidity", "P");
  // legend->Draw();
  // c1->SaveAs(Form("../graph/%s_humid.png", "HGCAL_cycle"));
  // c1->SaveAs(Form("../graph/%s_humid.pdf", "HGCAL_cycle"));
  
  //TF1 *fRY = new TF1("fRY", "x", 0, 100);
  //TGaxis *RYaxis = new TGaxis(tmin->Convert(), 0, tmax->Convert(), 80, "fRY", 80, "");
  //RYaxis->SetTitle("Humidity(%)");
  //RYaxis->Draw("SAME");
  
  

  /*
  TFile *save_graph = new TFile("DHT22_pt100_pt1000_test2.root", "RECREATE");
  g0->Write();
  g1->Write();
  g2->Write();
  g3->Write();
  g4->Write();
  g5->Write();
  g6->Write();
  //mg_temp->Write();
  //mg_humid->Write();
  save_graph->Close();
  */
  
}
