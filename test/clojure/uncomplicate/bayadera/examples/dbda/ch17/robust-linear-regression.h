REAL rlr_loglik(__constant const REAL* params, REAL* x) {

    const REAL nu = x[0];
    const REAL b0 = x[1];
    const REAL b1 = x[2];
    const REAL sigma = x[3];

    const uint n = (uint)params[0];

    const bool valid = (0.0f < nu) && (0.0f < sigma);

    if (valid) {
        const REAL scale = t_log_scale(nu, sigma);
        REAL res = 0.0;
        for (uint i = 0; i < n; i = i+2) {
            res += t_log_unscaled(nu, b0 + b1 * params[i+1], sigma, params[i+2])
                + scale;
        }
        return res;
    }
    return NAN;

}

REAL rlr_mcmc_logpdf(__constant const REAL* params, REAL* x) {
    const bool valid = (1.0f < x[0]);
    if (valid) {
        return exponential_log_unscaled(params[0], x[0] - 1)
            + gaussian_log_unscaled(params[1], params[2], x[1])
            + gaussian_log_unscaled(params[3], params[4], x[2])
            + uniform_log(params[5], params[6], x[3]);
    }
    return NAN;

}

REAL rlr_logpdf(__constant const REAL* params, REAL* x) {
    return exponential_log(params[0], x[0] - 1)
        + gaussian_log(params[1], params[2], x[1])
        + gaussian_log(params[3], params[4], x[2])
        + uniform_log(params[5], params[6], x[3]);

}
