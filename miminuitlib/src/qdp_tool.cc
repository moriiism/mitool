#include "mim_qdp_tool.h"

void MimQdpTool::MkQdpMinFcn(const HistData1d* const hist_data,
                              string outqdp,
                              double xval_at_fcnmin,
                              double xval_terr_minus,
                              double xval_terr_plus,
                              double fcnmin,
                              string title_xval)
{
    FILE *fp = fopen(outqdp.c_str(), "w");
    fprintf(fp, "skip sing \n");
    fprintf(fp, "\n");
    hist_data->PrintData(fp, "x,y");
    fprintf(fp, "\n");
    fprintf(fp, "csize 1.5\n");
    fprintf(fp, "line on \n");
    fprintf(fp, "mark 22 on \n");
    fprintf(fp, "view 0.2 0.1 0.95 0.95\n");
    fprintf(fp, "la pos y 4.0\n");

    double x_lo, x_up;
    hist_data->GetXRangeQdp(&x_lo, &x_up);
    double y_lo, y_up;
    hist_data->GetORangeQdp(&y_lo, &y_up);
    
    double oval_1sigma   = fcnmin + Minfcn::GetUpMinfcn(1.0, "sigma", 1);
    double oval_90cl1p   = fcnmin + Minfcn::GetUpMinfcn(0.90, "cl", 1);
    double oval_99cl1p   = fcnmin + Minfcn::GetUpMinfcn(0.99, "cl", 1);

    int ilab = 1;

    // horizontal lines
    // line at chi2min
    fprintf(fp, "la %d pos %.15e %.15e \" \" line 0.0 1.0 lst 4\n",
            ilab, x_lo, fcnmin);
    ilab ++;
    fprintf(fp, "la %d pos %.15e %.15e \"%s\" jus left cen bot csize 1.2\n",
            ilab, x_lo, fcnmin, "best");
    ilab ++;

    // line at chi2min + 1 sigma
    fprintf(fp, "la %d pos %.15e %.15e \" \" line 0.0 1.0 lst 4\n",
            ilab, x_lo, oval_1sigma);
    ilab ++;
    fprintf(fp, "la %d pos %.15e %.15e \"%s\" jus left cen bot csize 1.2\n",
            ilab, x_lo, oval_1sigma, "1sigma");
    ilab ++;

    // line at chi2min + 90%CL
    fprintf(fp, "la %d pos %.15e %.15e \" \" line 0.0 1.0 lst 4\n",
            ilab, x_lo, oval_90cl1p);
    ilab ++;
    fprintf(fp, "la %d pos %.15e %.15e \"%s\" jus left cen bot csize 1.2\n",
            ilab, x_lo, oval_90cl1p, "90%CL");
    ilab ++;

    // line at chi2min + 99%CL
    fprintf(fp, "la %d pos %.15e %.15e \" \" line 0.0 1.0 lst 4\n",
            ilab, x_lo, oval_99cl1p);
    ilab ++;
    fprintf(fp, "la %d pos %.15e %.15e \"%s\" jus left cen bot csize 1.2\n",
            ilab, x_lo, oval_99cl1p, "99%CL");
    ilab ++;

    // vertical lines
    double pos_y_print = y_up - (y_up - y_lo) * 0.05;
    double pos_x_shift_print = (x_up - x_lo) * 0.01;
        
    // line at chi2min
    fprintf(fp, "la %d pos %.15e %.15e \" \" line 90.0 1.0 lst 4\n",
            ilab, xval_at_fcnmin, y_lo);
    ilab ++;
    fprintf(fp, "la %d pos %.15e %.15e \"%.3e\" rot 90 jus right cen bot csize 1.2\n",
            ilab, xval_at_fcnmin - pos_x_shift_print, pos_y_print,  xval_at_fcnmin);
    ilab ++;

    // line at chi2min - 1 sigma
    fprintf(fp, "la %d pos %.15e %.15e \" \" line 90.0 1.0 lst 4\n",
            ilab, xval_at_fcnmin + xval_terr_minus, y_lo);
    ilab ++;
    fprintf(fp, "la %d pos %.15e %.15e \"%.3e\" rot 90 jus right cen bot csize 1.2\n",
            ilab, xval_at_fcnmin + xval_terr_minus - pos_x_shift_print, pos_y_print,
            xval_at_fcnmin  + xval_terr_minus);
    ilab ++;

    // line at chi2min + 1 sigma
    fprintf(fp, "la %d pos %.15e %.15e \" \" line 90.0 1.0 lst 4\n",
            ilab, xval_at_fcnmin + xval_terr_plus, y_lo);
    ilab ++;
    fprintf(fp, "la %d pos %.15e %.15e \"%.3e\" rot 90 jus right cen bot csize 1.2\n",
            ilab, xval_at_fcnmin + xval_terr_plus - pos_x_shift_print, pos_y_print,
            xval_at_fcnmin  + xval_terr_plus);
    ilab ++;

    fprintf(fp, "la rot\n");
    fprintf(fp, "la file\n");
    fprintf(fp, "time off\n");
    fprintf(fp, "la y fcn (chi2 or c-stat)\n");
    fprintf(fp, "la t %s\n", hist_data->GetTitle().c_str());
    fprintf(fp, "r x %.15e %.15e\n", x_lo, x_up);
    fprintf(fp, "r y %.15e %.15e\n", y_lo, y_up);
    fprintf(fp, "la x %s\n", title_xval.c_str());
  
    fclose(fp);
}

//
// contour
//

void MimQdpTool::MkQdpCont(const HistData2d* const h2d,
                            string qdpout, int ncont,
                            string title_xval,
                            string title_yval,
                            string title_oval,
                            double offset_xval,
                            double offset_yval,
                            double offset_oval)
{
    long nbin_xval = h2d->GetNbinX();
    long nbin_yval = h2d->GetNbinY();
    double xval_lo = h2d->GetXvalLo();
    double xval_up = h2d->GetXvalUp();
    double yval_lo = h2d->GetYvalLo();
    double yval_up = h2d->GetYvalUp();
    
    double xval_step = (xval_up - xval_lo)/ nbin_xval;
    double yval_step = (yval_up - yval_lo)/ nbin_yval;

    double xval_lo_qdpcont = xval_lo + 0.5 * xval_step;
    double xval_up_qdpcont = xval_up - 0.5 * xval_step;
    double yval_lo_qdpcont = yval_lo + 0.5 * yval_step;    
    double yval_up_qdpcont = yval_up - 0.5 * yval_step;

    double xval_lo_qdpcont_new = xval_lo_qdpcont - offset_xval;
    double xval_up_qdpcont_new = xval_up_qdpcont - offset_xval;
    double yval_lo_qdpcont_new = yval_lo_qdpcont - offset_yval;
    double yval_up_qdpcont_new = yval_up_qdpcont - offset_yval;

  
    FILE* fp = fopen(qdpout.c_str(), "w");
    fprintf(fp, "\n");
    for(long index_xval = 0; index_xval < nbin_xval; index_xval++){
        for(long index_yval = 0; index_yval < nbin_yval - 1; index_yval++){
            fprintf(fp, "  %e ", h2d->GetOvalElm(index_xval, index_yval) - offset_oval);
        }
        fprintf(fp, "  %e\n", h2d->GetOvalElm(index_xval, nbin_yval - 1) - offset_oval);
    }
  
    fprintf(fp, "\n");
    fprintf(fp, "COlor OFf 1..999\n");
    fprintf(fp, "xax lin  %.5e  %.5e\n", xval_lo_qdpcont_new, xval_step);
    fprintf(fp, "yax lin  %.5e  %.5e\n", yval_lo_qdpcont_new, yval_step);
  
    fprintf(fp, "\n");
    fprintf(fp, "lw 5\n");
    fprintf(fp, "la rot \n");
    fprintf(fp, "la pos y 2.5\n");
    fprintf(fp, "grid on\n");
    fprintf(fp, "lst 4 on grid\n");
    
    double zval_min = h2d->GetOvalArr()->GetValMin();
    double zval_max = h2d->GetOvalArr()->GetValMax();
    double zval_range = zval_max - zval_min;
    zval_min = zval_min - zval_range * 0.1;
    zval_max = zval_max + zval_range * 0.1;
    double zstep = (zval_max - zval_min) / ncont;

    fprintf(fp, "ima min %.5e max %.5e cct 2 cb\n", zval_min, zval_max);
    
    double* cont_level_arr = new double [ncont];
    for(int icont = 0; icont < ncont; icont++){
        cont_level_arr[icont] = zval_min + (icont + 0.5) * zstep;
    }

    fprintf(fp, "DG     1       1      1     %ld     %ld\n",  nbin_xval, nbin_yval);

    char cmd_cont[1000];
    char cmd_col[1000];
    char cmd_lst[1000];
    char cmd_lw[1000];
    sprintf(cmd_cont, "CONT  1 LEVEL ");
    sprintf(cmd_col, "CONT  1 COLOR ");
    sprintf(cmd_lst, "CONT  1 LSTYL ");
    sprintf(cmd_lw, "CONT  1 LWID ");
    for(int icont = 0; icont < ncont; icont++){
        sprintf(cmd_cont, "%s  %.15e  ", cmd_cont, cont_level_arr[icont]);
        sprintf(cmd_col,  "%s  %d  ", cmd_col, icont + 1);
        sprintf(cmd_lst,  "%s  %d  ", cmd_lst, 1);
        sprintf(cmd_lw,   "%s  %d  ", cmd_lw,  5);
    }
    fprintf(fp, "%s\n", cmd_cont);
    fprintf(fp, "%s\n", cmd_col);
    fprintf(fp, "%s\n", cmd_lst);
    fprintf(fp, "%s\n", cmd_lw);
    fprintf(fp, "r x %.5e %.5e\n", xval_lo_qdpcont_new, xval_up_qdpcont_new);
    fprintf(fp, "r y %.5e %.5e\n", yval_lo_qdpcont_new, yval_up_qdpcont_new);
    fprintf(fp, "la x %s (offset = %.5e)\n", title_xval.c_str(), offset_xval);
    fprintf(fp, "la y %s (offset = %.5e)\n", title_yval.c_str(), offset_yval);
    fprintf(fp, "la file\n");
    fprintf(fp, "time off\n");

    delete [] cont_level_arr;
  
    fclose(fp);
}


void MimQdpTool::MkQdpContMinFcn(const HistData2d* const h2d,
                                  string qdpout,
                                  string title_xval,
                                  string title_yval,
                                  string title_oval,
                                  double offset_xval,
                                  double offset_yval,
                                  double offset_oval)
{
    double zval_best = h2d->GetOvalArr()->GetValMin();
    double xval_best, yval_best;
    h2d->GetBinCenterXYFromIbin(h2d->GetOvalArr()->GetLocValMin(), &xval_best, &yval_best);
    MkQdpContMinFcnWithBest(h2d, qdpout,
                            xval_best, yval_best, zval_best,
                            title_xval, title_yval, title_oval,
                            offset_xval, offset_yval, offset_oval);
}

void MimQdpTool::MkQdpContMinFcnWithBest(const HistData2d* const h2d,
                                          string qdpout,
                                          double xval_best,
                                          double yval_best,
                                          double zval_best,
                                          string title_xval,
                                          string title_yval,
                                          string title_oval,
                                          double offset_xval,
                                          double offset_yval,
                                          double offset_oval)
{
    long nbin_xval = h2d->GetNbinX();
    long nbin_yval = h2d->GetNbinY();
    double xval_lo = h2d->GetXvalLo();
    double xval_up = h2d->GetXvalUp();
    double yval_lo = h2d->GetYvalLo();
    double yval_up = h2d->GetYvalUp();    

    double xval_step = (xval_up - xval_lo)/ nbin_xval;
    double yval_step = (yval_up - yval_lo)/ nbin_yval;

    double xval_lo_qdpcont = xval_lo + 0.5 * xval_step;
    double yval_lo_qdpcont = yval_lo + 0.5 * yval_step;
    double xval_up_qdpcont = xval_up - 0.5 * xval_step;
    double yval_up_qdpcont = yval_up - 0.5 * yval_step;

    double xval_range = xval_up_qdpcont - xval_lo_qdpcont;
    double yval_range = yval_up_qdpcont - yval_lo_qdpcont;

    double xval_lo_qdpcont_new = xval_lo_qdpcont - offset_xval;
    double xval_up_qdpcont_new = xval_up_qdpcont - offset_xval;
    double yval_lo_qdpcont_new = yval_lo_qdpcont - offset_yval;
    double yval_up_qdpcont_new = yval_up_qdpcont - offset_yval;

  
    FILE* fp = fopen(qdpout.c_str(), "w");
    fprintf(fp, "\n");
    for(long index_xval = 0; index_xval < nbin_xval; index_xval++){
        for(long index_yval = 0; index_yval < nbin_yval - 1; index_yval++){
            fprintf(fp, "  %.5e ", h2d->GetOvalElm(index_xval, index_yval) - offset_oval);
        }
        fprintf(fp, "  %.5e\n", h2d->GetOvalElm(index_xval, nbin_yval - 1) - offset_oval);
    }

    fprintf(fp, "\n");
    fprintf(fp, "COlor OFf 1..999\n");
    fprintf(fp, "xax lin  %.5e  %.5e\n", xval_lo_qdpcont_new, xval_step);
    fprintf(fp, "yax lin  %.5e  %.5e\n", yval_lo_qdpcont_new, yval_step);
  
    fprintf(fp, "\n");
    fprintf(fp, "lw 5\n");
    fprintf(fp, "la rot \n");
    fprintf(fp, "la pos y 2.5\n");

    double xval_at_zmin = xval_best;
    double yval_at_zmin = yval_best;
    double zmin = zval_best;

    double xval_at_zmin_new = xval_at_zmin - offset_xval;
    double yval_at_zmin_new = yval_at_zmin - offset_yval;
    double zmin_new = zmin - offset_oval;
  
    double cont_level_0 = zmin_new + Minfcn::GetUpMinfcn(1.0, "sigma", 1);
    double cont_level_1 = zmin_new + Minfcn::GetUpMinfcn(0.900, "cl", 1);
    double cont_level_2 = zmin_new + Minfcn::GetUpMinfcn(0.900, "cl", 2);

    fprintf(fp, "DG     1       1      1     %ld     %ld\n",  nbin_xval, nbin_yval);
    fprintf(fp, "CONT  1 LEVEL  %.5e   %.5e   %.5e\n",
            cont_level_0, cont_level_1, cont_level_2);
    fprintf(fp, "CONT  1 COLOR       1       2       3\n");
    fprintf(fp, "CONT  1 LSTYL       1       1       1\n");
    fprintf(fp, "CONT  1 LWID        5       5       5\n");

    fprintf(fp, "lab 1 pos %.5e %.5e \"+\"\n", xval_at_zmin_new, yval_at_zmin_new);
    fprintf(fp, "LAB 2 csize 1.0 CEN Top JUS Lef\n");
    fprintf(fp, "LAB 2 POS %.5e %.5e \"\\gx\\u2\\d\\dmin\\u = %.5e @ (%.2e, %.2e)\"\n",
            xval_lo_qdpcont_new + xval_range * 0.05,
            yval_lo_qdpcont_new + yval_range * 0.95,
            zmin_new, xval_at_zmin, yval_at_zmin);
    fprintf(fp, "LAB 3 csize 1.0 CEN Top JUS Lef\n");
    fprintf(fp, "LAB 3 POS %.5e %.5e \"\\gD\\gx\\u2\\d = %.2e (1\\gs: 1 par)\"\n",
            xval_lo_qdpcont_new + xval_range * 0.05,
            yval_lo_qdpcont_new + yval_range * 0.90,
            cont_level_0 - zmin_new);
    fprintf(fp, "LAB 4 csize 1.0 CEN Top JUS Lef\n");
    fprintf(fp, "LAB 4 POS %.5e %.5e \"\\gD\\gx\\u2\\d = %.2e (90%%CL: 1 par)\"\n",
            xval_lo_qdpcont_new + xval_range * 0.05,
            yval_lo_qdpcont_new + yval_range * 0.85,
            cont_level_1 - zmin_new);  
    fprintf(fp, "LAB 5 csize 1.0 CEN Top JUS Lef\n");
    fprintf(fp, "LAB 5 POS %.5e %.5e \"\\gD\\gx\\u2\\d = %.2e (90%%CL: 2 par)\"\n",
            xval_lo_qdpcont_new + xval_range * 0.05,
            yval_lo_qdpcont_new + yval_range * 0.80,
            cont_level_2 - zmin_new);  

    fprintf(fp, "r x %.5e %.5e\n", xval_lo_qdpcont_new, xval_up_qdpcont_new);
    fprintf(fp, "r y %.5e %.5e\n", yval_lo_qdpcont_new, yval_up_qdpcont_new);
    fprintf(fp, "la x %s\n", title_xval.c_str());
    fprintf(fp, "la y %s\n", title_oval.c_str());
  
    fclose(fp);
}

