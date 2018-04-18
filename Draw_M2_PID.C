void eraseBottomLabel(TPad *p,Double_t h)
{
   p->cd();
   TPad * pe = new TPad("pe","pe",0,0,p->GetLeftMargin()*0.96,h);       
   pe->Draw(); 
   pe->SetFillColor(p->GetFillColor());  
   pe->SetBorderMode(0);
}

void Draw_M2_PID(TString inFileName)
{
  TFile * iFile     = new TFile(inFileName.Data(),"read");
  TFile * styleFile = new TFile("/home/peter/Documents/WorkLocal/MPD/RootFiles/TDR/my_style.root");
  
  TStyle * style = (TStyle*) styleFile -> Get("style");
  gROOT -> ForceStyle();
  style -> cd();
  
  const Double_t PIDptBins  []          = {0.,0.2,0.5,1.,1.5,2.,3.};
  const Int_t    PIDNpt                 = 6;
  const Double_t PIDetaBins []          = {-1.5,-1.,0.,1.,1.5};
  const Int_t    PIDNeta                = 4;
  TString  PIDparticleBins [] = {TString("pion"), TString("kaon"), TString("proton")}; 
  const Int_t    PIDNparticles          = 3;
  const Int_t    PIDNhist                   = 100;
  const Double_t PIDMass2 []            = {0.1396*0.1396,0.4937*0.4937,0.9383*0.9383};
  const Double_t PIDMass2Width []       = {PIDMass2[0]*1.,PIDMass2[1]*1.,PIDMass2[2]*1.};
  const Int_t    PIDpdg []              = {211, 321, 2212};
  const Int_t    PIDTofFlags []         = {0,2,4,6};
  const Int_t    PIDNTofFlag            = 4;
  
  const Double_t PadXmin []             = {0.   ,0.33 ,0.66 ,0.   ,0.33 ,0.66 };
  const Double_t PadXmax []             = {0.33 ,0.66 ,1.   ,0.33 ,0.66 ,1.   };
  const Double_t PadYmin []             = {0.5  ,0.5  ,0.5  ,0.   ,0.   ,0.   };
  const Double_t PadYmax []             = {1.   ,1.   ,1.   ,0.5  ,0.5  ,0.5  };
    
  const Double_t PadBorderLeftSize []   = {0.2,0.2,0.2,0.2,0.2,0.2};
  const Double_t PadBorderRightSize []  = {0.,0.,0.,0.,0.,0.};
  const Double_t PadBorderTopSize []    = {0.,0.,0.,0.,0.,0.};
  const Double_t PadBorderBottomSize [] = {0.2,0.2,0.2,0.2,0.2,0.2};
  
  const Int_t PionPtBinDraw []          = {0,1,2,0,1,2};
  const Int_t KaonPtBinDraw []          = {0,1,2,0,1,2};
  const Int_t ProtonPtBinDraw []        = {0,1,2,0,1,2};
  
  const Int_t PionPtBinDraw1 []         = {3,4,5,3,4,5};
  const Int_t KaonPtBinDraw1 []         = {3,4,5,3,4,5};
  const Int_t ProtonPtBinDraw1 []       = {3,4,5,3,4,5};
  
  const Int_t PionEtaBinDraw []         = {0,0,0,1,1,1};
  
  //const Int_t PionEtaBinDraw []         = {3,3,3,2,2,2};
  
  //Int_t PtBinDraw[6][6] = {{0,1,2,0,1,2},{3,4,5,3,4,5},{1,2,3,1,2,3},{0,4,5,0,4,5},{1,2,3,1,2,3},{0,4,5,0,4,5}};
  Int_t PtBinDraw[6][6] = {{0,1,2,0,1,2},{3,4,5,3,4,5},{0,1,2,0,1,2},{3,4,5,3,4,5},{0,1,2,0,1,2},{3,4,5,3,4,5}};
  
  const Int_t ParticleBinDraw []        = {0,0,1,1,2,2};
  
  const Int_t MarkerStyle []            = {20,20,24,25,26};
  const Int_t MarkerColor []            = {1,2,597,419,430};
  
  const Double_t PtCoeff []             = {1.,1.,1.}; //{0.6,1.5,2.};
  
  TH1F* hPIDm2[PIDNparticles][PIDNpt][PIDNeta];
  TH1F* hPIDm2Before[PIDNparticles][PIDNpt][PIDNeta];
  TH1F* hPIDm2PDGpion[PIDNparticles][PIDNpt][PIDNeta];
  TH1F* hPIDm2PDGkaon[PIDNparticles][PIDNpt][PIDNeta];
  TH1F* hPIDm2PDGproton[PIDNparticles][PIDNpt][PIDNeta];
  
  for (int ParticleIterator=0; ParticleIterator < PIDNparticles; ParticleIterator++){
    for (int PtIterator=0; PtIterator < PIDNpt; PtIterator++){
      for (int EtaIterator=0;EtaIterator < PIDNeta; EtaIterator++){
        std::cout << "Getting TH1F*: " << ParticleIterator << " " << PtIterator << " " << EtaIterator << std::endl;
        hPIDm2[ParticleIterator][PtIterator][EtaIterator]           = (TH1F*) iFile->Get(Form("mass2/hPIDmSqr%i%i%i",ParticleIterator,PtIterator,EtaIterator));
        hPIDm2Before[ParticleIterator][PtIterator][EtaIterator]     = (TH1F*) iFile->Get(Form("mass2/hPIDmSqrBeforeCut%i%i%i",ParticleIterator,PtIterator,EtaIterator));
        hPIDm2PDGpion[ParticleIterator][PtIterator][EtaIterator]    = (TH1F*) iFile->Get(Form("mass2/hPIDmSqrPDGpion%i%i%i",ParticleIterator,PtIterator,EtaIterator));
        hPIDm2PDGkaon[ParticleIterator][PtIterator][EtaIterator]    = (TH1F*) iFile->Get(Form("mass2/hPIDmSqrPDGkaon%i%i%i",ParticleIterator,PtIterator,EtaIterator));
        hPIDm2PDGproton[ParticleIterator][PtIterator][EtaIterator]  = (TH1F*) iFile->Get(Form("mass2/hPIDmSqrPDGproton%i%i%i",ParticleIterator,PtIterator,EtaIterator));
      }
    }
  }

  TCanvas * canv[6];
  TPad * pads[6][6];
  TLegend *leg[6][6];
  for (int iPid = 0; iPid < 6; iPid++){
    canv[iPid] = new TCanvas(Form("canv%i",iPid),Form("%i: m^{2} of %s",iPid, PIDparticleBins[ParticleBinDraw[iPid]].Data()),1280,720);
    canv[iPid] -> cd();
    for (int iPads=0; iPads < 6; iPads++){
      pads[iPid][iPads] = new TPad(Form("pad%i%i",iPid, iPads),Form("pad%i%i",iPid, iPads),PadXmin[iPads],PadYmin[iPads],PadXmax[iPads],PadYmax[iPads]);
      std::cout << "TPad: " << pads[iPid][iPads]->GetName() << " x_min: " << PadXmin[iPads] <<" x_max: " <<
                   PadXmax[iPads] << " y_min: " << PadYmin[iPads] << " y_max: " << PadYmax[iPads] << std::endl;
      pads[iPid][iPads] -> SetLeftMargin(PadBorderLeftSize[iPads]);
      pads[iPid][iPads] -> SetRightMargin(PadBorderRightSize[iPads]);
      pads[iPid][iPads] -> SetTopMargin(PadBorderTopSize[iPads]);
      pads[iPid][iPads] -> SetBottomMargin(PadBorderBottomSize[iPads]);
      
      pads[iPid][iPads] -> SetLogy();
      pads[iPid][iPads] -> GetFrame() -> SetFillColor(0);
      pads[iPid][iPads] -> Draw();
      
      leg[iPid][iPads] = new TLegend(0.23,0.8,0.99,0.99);
    }
  }
  
  Int_t PtBin,EtaBin,PidBin;
  TString HistTitle;
  for (int iPid = 0; iPid < 6; iPid++){
    for (int iPads=0; iPads < 6; iPads++){
      pads[iPid][iPads] -> cd();
      PidBin = -1; EtaBin = -1; PtBin = -1;
      {
        //if (iPid % 2 == 0) PtBin = PionPtBinDraw[iPads];
        //if (iPid % 2 != 0) PtBin = PionPtBinDraw1[iPads];
        PtBin = PtBinDraw[iPid][iPads];
        PidBin = ParticleBinDraw[iPid]; EtaBin = PionEtaBinDraw[iPads];
      }
      
      std::cout << iPid << "| iPid: " << PidBin << " iPt: " << PtBin << " iEta: " << EtaBin << std::endl;
      
      hPIDm2Before[PidBin][PtBin][EtaBin] -> SetMarkerStyle(MarkerStyle[0]);
      hPIDm2Before[PidBin][PtBin][EtaBin] -> SetMarkerColor(MarkerColor[0]);
      hPIDm2Before[PidBin][PtBin][EtaBin] -> SetLineColor(MarkerColor[0]);
      
      hPIDm2[PidBin][PtBin][EtaBin] -> SetMarkerStyle(MarkerStyle[1]);
      hPIDm2[PidBin][PtBin][EtaBin] -> SetMarkerColor(MarkerColor[1]);
      hPIDm2[PidBin][PtBin][EtaBin] -> SetLineColor(MarkerColor[1]);
      
      hPIDm2PDGpion[PidBin][PtBin][EtaBin] -> SetMarkerStyle(MarkerStyle[2]);
      hPIDm2PDGpion[PidBin][PtBin][EtaBin] -> SetMarkerColor(MarkerColor[2]);
      hPIDm2PDGpion[PidBin][PtBin][EtaBin] -> SetLineColor(MarkerColor[2]);
      hPIDm2PDGpion[PidBin][PtBin][EtaBin] -> SetLineStyle(2);
      
      hPIDm2PDGkaon[PidBin][PtBin][EtaBin] -> SetMarkerStyle(MarkerStyle[3]);
      hPIDm2PDGkaon[PidBin][PtBin][EtaBin] -> SetMarkerColor(MarkerColor[3]);
      hPIDm2PDGkaon[PidBin][PtBin][EtaBin] -> SetLineColor(MarkerColor[3]);
      hPIDm2PDGkaon[PidBin][PtBin][EtaBin] -> SetLineStyle(2);
      
      hPIDm2PDGproton[PidBin][PtBin][EtaBin] -> SetMarkerStyle(MarkerStyle[4]);
      hPIDm2PDGproton[PidBin][PtBin][EtaBin] -> SetMarkerColor(MarkerColor[4]);
      hPIDm2PDGproton[PidBin][PtBin][EtaBin] -> SetLineColor(MarkerColor[4]);
      hPIDm2PDGproton[PidBin][PtBin][EtaBin] -> SetLineStyle(2);
      
      hPIDm2Before[PidBin][PtBin][EtaBin] -> GetYaxis() -> CenterTitle();
      //hPIDm2Before[PidBin][PtBin][EtaBin] -> GetYaxis() -> SetRangeUser(0.1,1.4*hPIDm2Before[PidBin][PtBin][EtaBin] -> GetBinContent(51) + 5*hPIDm2Before[PidBin][PtBin][EtaBin] -> GetBinError(51));
      
      //std::cout << hPIDm2Before[PidBin][PtBin][EtaBin] -> GetBinContent(51) << " " << TMath::Power(10,TMath::Log10(hPIDm2Before[PidBin][PtBin][EtaBin] -> GetBinContent(51) )*3/2 ) << std::endl;
      
      //if ( hPIDm2Before[PidBin][PtBin][EtaBin] -> GetMinimum() < hPIDm2Before[PidBin][PtBin][EtaBin] -> GetBinContent(51) )
        //hPIDm2Before[PidBin][PtBin][EtaBin] -> GetYaxis() -> SetRangeUser(hPIDm2Before[PidBin][PtBin][EtaBin] -> GetMinimum(),TMath::Power(10,TMath::Log10(hPIDm2Before[PidBin][PtBin][EtaBin] -> GetBinContent(51) - hPIDm2Before[PidBin][PtBin][EtaBin] -> GetMinimum() )*3.5/2) + hPIDm2Before[PidBin][PtBin][EtaBin] -> GetMinimum() );
      //else
        //hPIDm2Before[PidBin][PtBin][EtaBin] -> GetYaxis() -> SetRangeUser(0.1,TMath::Power(10,TMath::Log10(hPIDm2Before[PidBin][PtBin][EtaBin] -> GetBinContent(51) )*3.5/2) );
      
      hPIDm2Before[PidBin][PtBin][EtaBin] -> GetXaxis() -> SetRangeUser( (PIDMass2[PidBin] - 0.5*PtCoeff[PtBin]*PIDMass2Width[PidBin]), (PIDMass2[PidBin] + 0.5*PtCoeff[PtBin]*PIDMass2Width[PidBin]));
      
      hPIDm2Before[PidBin][PtBin][EtaBin] -> GetYaxis() -> SetRangeUser(1.1,5e7 );

      hPIDm2Before[PidBin][PtBin][EtaBin] -> GetXaxis() -> SetNdivisions(9);
      hPIDm2Before[PidBin][PtBin][EtaBin] -> GetYaxis() -> SetNdivisions(9);
      
      HistTitle = hPIDm2[PidBin][PtBin][EtaBin] -> GetTitle();
      hPIDm2Before[PidBin][PtBin][EtaBin] -> SetTitle("");
      leg[iPid][iPads] -> SetNColumns(3);
      leg[iPid][iPads] -> SetHeader(HistTitle.Data(),"C");
      leg[iPid][iPads] -> AddEntry(hPIDm2Before[PidBin][PtBin][EtaBin],"No PID");
      leg[iPid][iPads] -> AddEntry(hPIDm2[PidBin][PtBin][EtaBin],"PID");
      //leg[iPid][iPads] -> AddEntry((TObject*)0,"","");
      //leg[iPid][iPads] -> AddEntry(hPIDm2PDGpion[PidBin][PtBin][EtaBin],"Pions (PDG)");
      //leg[iPid][iPads] -> AddEntry(hPIDm2PDGkaon[PidBin][PtBin][EtaBin],"Kaons (PDG)");
      //leg[iPid][iPads] -> AddEntry(hPIDm2PDGproton[PidBin][PtBin][EtaBin],"Protons (PDG)");
      
      //if (PidBin == 1 && PtBin == 5 && EtaBin == 0){ std::cout << hPIDm2[PidBin][PtBin][EtaBin] -> GetEntries() <<std::endl; continue;}
      //if (hPIDm2[PidBin][PtBin][EtaBin] -> GetEntries() < 1e3) continue;
      hPIDm2Before[PidBin][PtBin][EtaBin] ->Draw("");
      hPIDm2[PidBin][PtBin][EtaBin] ->Draw("same");
      //hPIDm2PDGpion[PidBin][PtBin][EtaBin] ->Draw("same");
      //hPIDm2PDGkaon[PidBin][PtBin][EtaBin] ->Draw("same");
      //hPIDm2PDGproton[PidBin][PtBin][EtaBin] ->Draw("same");
      
      leg[iPid][iPads] -> Draw();
      
      eraseBottomLabel(pads[iPid][iPads],hPIDm2[PidBin][PtBin][EtaBin] ->GetXaxis()->GetLabelSize());
    }
    
    canv[iPid] -> SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/PID/M2_canv%i.png",iPid));
    canv[iPid] -> SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/PID/M2_canv%i.pdf",iPid));
    
  }
}
