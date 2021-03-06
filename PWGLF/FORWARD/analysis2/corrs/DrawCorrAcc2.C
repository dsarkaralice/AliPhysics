/**
 * @file 
 * 
 * Scripts to draw energy loss fits from correction object file 
 *
 * @ingroup pwglf_forward_scripts_corr
 */
/** 
 * Clear canvas 
 * 
 * @param c Canvas to clear 
 *
 * @ingroup pwglf_forward_scripts_corr
 */
void
ClearCanvas(TCanvas* c)
{
  c->SetLeftMargin(.1);
  c->SetRightMargin(.05);
  c->SetBottomMargin(.1);
  c->SetTopMargin(.05);
  c->Clear();
}

/** 
 * Draw energy loss fits to a multi-page PDF. 
 *
 * @par Input: 
 * The input file is expected to contain a AliFMDCorrELossFit object
 * named @c elossfits in the top level directory.
 * 
 * @par Output: 
 * A multi-page PDF.  Note, that the PDF generated by ROOT in this way
 * is broken (cannot be read by Acrobat Reader on Windows and MacOSX)
 * and one should pass it through a filter to correct these problems.
 * 
 * @param fname   File name 
 * @param option  Drawing options 
 *
 * @ingroup pwglf_forward_scripts_corr
 */
void
DrawCorrAcc2(const char* fname, const char* option="colz")
{
  //__________________________________________________________________
  // Load libraries and object 
  gROOT->Macro("$ALICE_PHYSICS/PWGLF/FORWARD/analysis2/scripts/LoadLibs.C");

  TFile* file = TFile::Open(fname, "READ");
  if (!file) { 
    Error("DrawCorrAcc", "Failed to open %s", fname);
    return;
  }
  TString pname(fname);
  pname.ReplaceAll(".root", ".pdf");

  const char* objName = 
    AliForwardCorrectionManager::Instance()
    .GetObjectName(AliForwardCorrectionManager::kAcceptance);
  AliFMDCorrAcceptance* corr = 
    static_cast<AliFMDCorrAcceptance*>(file->Get(objName));
  if (!corr) { 
    Error("DrawCorrAcc", "Object '%s' not found in %s", objName, fname);
    return;
  }

  //__________________________________________________________________
  // Create a canvas
  // TCanvas* c = new TCanvas("c", "c", 800 / TMath::Sqrt(2), 800);
  TCanvas* c = new TCanvas("c", "c", 800, 800 / TMath::Sqrt(2));
  c->SetFillColor(0);
  c->SetBorderSize(0);
  c->SetBorderMode(0);
  
  gStyle->SetOptStat(0);
  gStyle->SetTitleColor(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleX(.5);
  gStyle->SetTitleY(1);
  gStyle->SetTitleW(.8);
  gStyle->SetTitleH(.09);
  gStyle->SetFrameFillColor(kWhite);
  gStyle->SetFrameBorderSize(1);
  gStyle->SetFrameBorderMode(1);
  gStyle->SetPalette(1);

  ClearCanvas(c);
  const TAxis& vtxAxis = corr->GetVertexAxis();
  Int_t        nVtx    = vtxAxis.GetNbins();
  c->Divide((nVtx+2)/3, 3, 0, 0);
  Int_t ipad = 0;

  //__________________________________________________________________
  // Draw all corrections
  for (UShort_t v = 1; v <= nVtx; v++) { 
    ipad++;
    if (ipad == 1 || ipad == 12) ipad++;

    TVirtualPad* p = c->cd(ipad);
    p->SetFillColor(kWhite);
        
    THStack* stack = new THStack(Form("vtx%02d", v),
				 Form("%+5.1f<v_{z}<%+5.1f",
				      vtxAxis.GetBinLowEdge(v),
				      vtxAxis.GetBinUpEdge(v)));
    for (UShort_t d = 1; d <= 3; d++) {
      UShort_t     nQ = (d == 1 ? 1 : 2);
      for (UShort_t q = 0; q < nQ; q++) { 
	Char_t r = (q == 0 ? 'I' : 'O');
	
	TH2* h1 = corr->GetCorrection(d, r, v);
	if (!h1) { 
	  Warning("DrawCorrAcc", "No correction for r=%c, v=%d", r, v);
	  continue;
	}
	Int_t nY = h1->GetNbinsY();
	TH1* hh = h1->ProjectionX(Form("FMD%d%c", d, r), 1, nY);
	hh->Scale(1. / nY);
	hh->SetDirectory(0);
	hh->SetMarkerColor(AliForwardUtil::RingColor(d, r));
	hh->SetLineColor(AliForwardUtil::RingColor(d, r));
	hh->SetFillColor(AliForwardUtil::RingColor(d, r));
	hh->SetFillStyle(3004);

	stack->Add(hh);
      }
    }
    stack->SetMaximum(1.2);
    stack->Draw("nostack");
  }
  //__________________________________________________________________
  // Close output file 
  c->SaveAs("acceptance.png");
}
//
// EOF
//
