void Draw_mom_res(){
    const TString p_name[] = {TString("pions"),TString("kaons"),TString("protons")};
    //const TString p_name[] = {TString("muons"),TString("kaons"),TString("protons")};
    const Int_t marker_style[] = {21,25};
    
    gStyle->SetOptStat(0);
    gStyle->SetErrorX(0);
    gStyle->SetFrameLineWidth(2);
    
    TFile* f_CF = new TFile("~/Documents/WorkLocal/MPD/RootFiles/mom_res_CF.root","read");
    TFile* f_HP = new TFile("~/Documents/WorkLocal/MPD/RootFiles/mom_res_HP.root","read");
    
    TProfile* p_mom[3][2];
    for (Int_t i=0;i<3;i++){
        for (Int_t j=0;j<2;j++){
            p_mom[i][0] = (TProfile*) f_HP->Get(Form("p_momenta_resolution%i",i));
            p_mom[i][1] = (TProfile*) f_CF->Get(Form("p_momenta_resolution%i",i));
            p_mom[i][0]->SetTitle(Form("%s",p_name[i].Data()));
        }
    }
    
    TCanvas* canv[3];
    TLegend* leg;
    for (Int_t i=0;i<3;i++){
        canv[i] = new TCanvas(Form("canv%i",i),Form("canv_%s",p_name[i].Data()),900,500);
        leg = new TLegend(0.65,0.71,0.86,0.84);
        leg->SetBorderSize(0);
        canv[i]->SetBottomMargin(0.19);
        canv[i]->SetLeftMargin(0.13);
        canv[i]->SetTicks(1,1);
        canv[i]->cd();
        p_mom[i][0]->SetMarkerStyle(marker_style[0]);
        p_mom[i][0]->SetMarkerSize(2.);
        p_mom[i][0]->SetLineWidth(3);
        p_mom[i][0]->SetMarkerColor(1);
        p_mom[i][0]->SetLineColor(1);
        
        p_mom[i][0]->GetXaxis()->SetTitle("p_{T},GeV/c");
        p_mom[i][0]->GetYaxis()->SetTitle("#Delta p_{T}/ p_{T}");
        p_mom[i][0]->SetTitleSize(0.08,"X");
        p_mom[i][0]->SetTitleSize(0.08,"Y");
        p_mom[i][0]->SetTitleOffset(0.75,"Y");
        p_mom[i][0]->SetLabelSize(0.06,"X");
        p_mom[i][0]->SetLabelSize(0.06,"Y");
        p_mom[i][0]->GetXaxis()->SetRangeUser(0.21,1.79);
        p_mom[i][0]->GetYaxis()->SetRangeUser(0.009,0.098);
        p_mom[i][0]->GetYaxis()->SetNdivisions(9);
        
        p_mom[i][1]->SetMarkerStyle(marker_style[1]);
        p_mom[i][1]->SetMarkerSize(2.);
        p_mom[i][1]->SetLineWidth(3);
        p_mom[i][1]->SetMarkerColor(2);
        p_mom[i][1]->SetLineColor(2);
        
        leg->AddEntry(p_mom[i][0],"Hit Producer","p");
        leg->AddEntry(p_mom[i][1],"Cluster Finder","p");
        
        p_mom[i][0]->Draw("X0");
        p_mom[i][1]->Draw("same,X0");
        leg->Draw();
        
        canv[i]->SaveAs(Form("~/Documents/WorkLocal/MPD/Pics/Mom_Res/Mom_res_%s_Box.png",p_name[i].Data()),"recreate");
    }
}