#include <vector>
#include <string>
#include <TEfficiency.h>
#include <TCanvas.h>
using namespace std;

void plotAllEff4(string inputFile)
{

  bool JETMET=false;
  if(inputFile.find("JETMET")!= std::string::npos)
    JETMET=true;

  TFile* f;
  TFile *inf = new TFile(inputFile.data());

  TEfficiency* fateff  =(TEfficiency*)inf->FindObjectAny("fatJetTotalEff");
  TEfficiency* thineff=(TEfficiency*)inf->FindObjectAny("thinJetTotalEff");


  fateff->SetLineColor(1);
  fateff->SetFillColor(1);
  fateff->SetFillStyle(3144);
  fateff->SetMarkerColor(1);
  fateff->SetMarkerStyle(8);
  fateff->SetMarkerSize(0.5);

  thineff->SetLineColor(2);
  thineff->SetFillColor(2);
  thineff->SetFillStyle(3144);
  thineff->SetMarkerColor(2);
  thineff->SetMarkerStyle(8);
  thineff->SetMarkerSize(0.5);
  fateff->SetTitle(";Generator-level Higgs p_{T} [GeV];Total Efficiency;");


  float x1NDC = 0.317;
  float y1NDC = 0.203;
  float x2NDC = 0.519;
  float y2NDC = 0.590;

  TLegend* leg = new TLegend(x1NDC,y1NDC,x2NDC,y2NDC);
  
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->SetTextSize(0.04);
  leg->SetBorderSize(0);
  leg->AddEntry(fateff, "merged jet + CSV efficiency","f");
  leg->AddEntry((TObject*)0, "single Anti-Kt R=0.8 jet","");
  leg->AddEntry((TObject*)0, "pt > 30 GeV, |#eta|<2.5","");
  leg->AddEntry((TObject*)0, "CISVV2>0.605","");
  if(JETMET)
    leg->AddEntry((TObject*)0, "#Delta R(H,jet)<0.1","");
  else
    leg->AddEntry((TObject*)0, "#Delta R(H,jet)<0.8","");
  leg->AddEntry((TObject*)0, "","");
  leg->AddEntry(thineff, "resolved jet + CSV efficiency","f");
  leg->AddEntry((TObject*)0, "two Anti-Kt R=0.4 jets","");
  leg->AddEntry((TObject*)0, "pt > 30 GeV, |#eta|<2.5","");
  leg->AddEntry((TObject*)0, "CISVV2>0.605","");
  if(JETMET)
    leg->AddEntry((TObject*)0, "#Delta R(b,jet)<0.1","");
  else
    leg->AddEntry((TObject*)0, "#Delta R(b,jet)<0.4","");

  TCanvas* c1 = new TCanvas("c1","",500,500);

  c1->SetGridx(1);
  c1->SetGridy(1);

  fateff->Draw("ae2");
  thineff->Draw("e2Same");  
  leg->Draw("same");

  std::string outputname = JETMET? "jeteff/effAll_smallMatchDeltaR": "jeteff/effAll_bigMatchDeltaR";
  c1->Print(Form("%s.pdf",outputname.data()));
  c1->Print(Form("%s.eps",outputname.data()));
  c1->Print(Form("%s.C",outputname.data()));



}
