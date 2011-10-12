                       svn_stream_t *outstream,
      SVN_ERR(svn_stream_printf_from_utf8(outstream, encoding, pool,
                                          _("   Reverse-merged %s:r%s%s"),
                                          from_path, merge_revstr->data,
                                          APR_EOL_STR));
      SVN_ERR(svn_stream_printf_from_utf8(outstream, encoding, pool,
                                          _("   Merged %s:r%s%s"),
                                          from_path, merge_revstr->data,
                                          APR_EOL_STR));
/* Adjust *PATH, *ORIG_PATH_1 and *ORIG_PATH_2, representing the changed file
                             const char *copyfrom_path,
                             svn_revnum_t copyfrom_rev,
                             const char *path,
  if (copyfrom_rev != SVN_INVALID_REVNUM)
    SVN_ERR(svn_stream_printf_from_utf8(os, header_encoding, result_pool,
                                        "copy from %s@%ld%s", copyfrom_path,
                                        copyfrom_rev, APR_EOL_STR));
  else
    SVN_ERR(svn_stream_printf_from_utf8(os, header_encoding, result_pool,
                                        "copy from %s%s", copyfrom_path,
                                        APR_EOL_STR));
 * revisions being diffed. COPYFROM_PATH and COPYFROM_REV indicate where the
 * diffed item was copied from.
                      svn_revnum_t copyfrom_rev,
                                           copyfrom_path, copyfrom_rev,
                                           repos_relpath2,
   to FILE.   Of course, OUTSTREAM will probably be whatever was
                   svn_stream_t *outstream,
  const char *path1 = orig_path1;
  const char *path2 = orig_path2;
  apr_pool_t *iterpool;
      const char *adjusted_path1 = path1;
      const char *adjusted_path2 = path2;
      SVN_ERR(svn_stream_printf_from_utf8(outstream, encoding, pool,
                                          "Index: %s" APR_EOL_STR
                                          "%s" APR_EOL_STR,
                                          path, equal_string));
        SVN_ERR(print_git_diff_header(outstream, &label1, &label2,
                                      svn_diff_op_modified,
                                      path1, path2, rev1, rev2, NULL,
                                      SVN_INVALID_REVNUM,
                                      encoding, pool));
      SVN_ERR(svn_stream_printf_from_utf8(outstream, encoding, pool,
  SVN_ERR(svn_stream_printf_from_utf8(outstream, encoding, pool,
                                      _("%sProperty changes on: %s%s"),
                                      APR_EOL_STR,
                                      use_git_diff_format ? path1 : path,
                                      APR_EOL_STR));
  SVN_ERR(svn_stream_printf_from_utf8(outstream, encoding, pool,
                                      "%s" APR_EOL_STR, under_string));
  iterpool = svn_pool_create(pool);
      svn_pool_clear(iterpool);

      SVN_ERR(svn_stream_printf_from_utf8(outstream, encoding, iterpool,
                                          "%s: %s%s", action,
                                          propchange->name, APR_EOL_STR));
                                                    outstream, iterpool);
        tmp = original_value ? original_value : svn_string_create("",
                                                                  iterpool);
        orig = maybe_append_eol(tmp, iterpool);
                                  svn_string_create("", iterpool);
        val = maybe_append_eol(tmp, iterpool);
        SVN_ERR(svn_diff_mem_string_diff(&diff, orig, val, &options,
                                         iterpool));
        SVN_ERR(svn_diff_mem_string_output_unified2(outstream, diff, FALSE,
                                                    "##",
                                           svn_dirent_local_style(path,
                                                                  iterpool),
                                           svn_dirent_local_style(path,
                                                                  iterpool),
                                           encoding, orig, val, iterpool));
  svn_pool_destroy(iterpool);
  svn_stream_t *outstream;
  svn_stream_t *errstream;
  /* Whether deletion of a file is summarized versus showing a full diff. */
  svn_boolean_t no_diff_deleted;

                   struct diff_cmd_baton *diff_cmd_baton,
                                 diff_cmd_baton->outstream,
                                            diff_cmd_baton,
                     svn_revnum_t copyfrom_rev,
                     struct diff_cmd_baton *diff_cmd_baton)
  svn_stream_t *errstream = diff_cmd_baton->errstream;
  svn_stream_t *outstream = diff_cmd_baton->outstream;
  const char *path1 = diff_cmd_baton->orig_path_1;
  const char *path2 = diff_cmd_baton->orig_path_2;
      SVN_ERR(svn_stream_printf_from_utf8(outstream,
               diff_cmd_baton->header_encoding, subpool,
      SVN_ERR(svn_stream_printf_from_utf8(outstream,
               diff_cmd_baton->header_encoding, subpool,
        SVN_ERR(svn_stream_printf_from_utf8(outstream,
                 diff_cmd_baton->header_encoding, subpool,
        SVN_ERR(svn_stream_printf_from_utf8(outstream,
                 diff_cmd_baton->header_encoding, subpool,
            SVN_ERR(svn_stream_printf_from_utf8(outstream,
                     diff_cmd_baton->header_encoding, subpool,
            SVN_ERR(svn_stream_printf_from_utf8(outstream,
                     diff_cmd_baton->header_encoding, subpool,
      apr_file_t *outfile;
      apr_file_t *errfile;
      const char *outfilename;
      const char *errfilename;
      svn_stream_t *stream;

      SVN_ERR(svn_stream_printf_from_utf8(outstream,
               diff_cmd_baton->header_encoding, subpool,
      /* We deal in streams, but svn_io_run_diff2() deals in file handles,
         unfortunately, so we need to make these temporary files, and then
         copy the contents to our stream. */
      SVN_ERR(svn_io_open_unique_file3(&outfile, &outfilename, NULL,
                                       svn_io_file_del_on_pool_cleanup,
                                       subpool, subpool));
      SVN_ERR(svn_io_open_unique_file3(&errfile, &errfilename, NULL,
                                       svn_io_file_del_on_pool_cleanup,
                                       subpool, subpool));

                               &exitcode, outfile, errfile,

      SVN_ERR(svn_io_file_close(outfile, subpool));
      SVN_ERR(svn_io_file_close(errfile, subpool));

      /* Now, open and copy our files to our output streams. */
      SVN_ERR(svn_stream_open_readonly(&stream, outfilename,
                                       subpool, subpool));
      SVN_ERR(svn_stream_copy3(stream, svn_stream_disown(outstream, subpool),
                               NULL, NULL, subpool));
      SVN_ERR(svn_stream_open_readonly(&stream, errfilename,
                                       subpool, subpool));
      SVN_ERR(svn_stream_copy3(stream, svn_stream_disown(errstream, subpool),
                               NULL, NULL, subpool));
          SVN_ERR(svn_stream_printf_from_utf8(outstream,
                   diff_cmd_baton->header_encoding, subpool,
              SVN_ERR(print_git_diff_header(outstream, &label1, &label2,
                                            operation,
                                            copyfrom_rev,
            SVN_ERR(svn_diff_file_output_unified3(outstream, diff,
                     tmpfile1, tmpfile2, label1, label2,

                                 svn_diff_op_modified, NULL,
                                 SVN_INVALID_REVNUM, diff_cmd_baton));
                               original_props, diff_cmd_baton, scratch_pool));
                                 copyfrom_revision, diff_cmd_baton));
                                 svn_diff_op_added, NULL, SVN_INVALID_REVNUM,
                                 diff_cmd_baton));
                               original_props, diff_cmd_baton, scratch_pool));
diff_file_deleted(svn_wc_notify_state_t *state,
                  svn_boolean_t *tree_conflicted,
                  const char *path,
                  const char *tmpfile1,
                  const char *tmpfile2,
                  const char *mimetype1,
                  const char *mimetype2,
                  apr_hash_t *original_props,
                  void *diff_baton,
                  apr_pool_t *scratch_pool)
  if (diff_cmd_baton->no_diff_deleted)
    {
      SVN_ERR(svn_stream_printf_from_utf8(diff_cmd_baton->outstream,
                diff_cmd_baton->header_encoding, scratch_pool,
                "Index: %s (deleted)" APR_EOL_STR "%s" APR_EOL_STR,
                path, equal_string));
    }
  else
    {
      if (tmpfile1)
        SVN_ERR(diff_content_changed(path,
                                     tmpfile1, tmpfile2,
                                     diff_cmd_baton->revnum1,
                                     diff_cmd_baton->revnum2,
                                     mimetype1, mimetype2,
                                     svn_diff_op_deleted, NULL,
                                     SVN_INVALID_REVNUM, diff_cmd_baton));
    }
static const svn_wc_diff_callbacks4_t diff_callbacks =
{
  diff_file_opened,
  diff_file_changed,
  diff_file_added,
  diff_file_deleted,
  diff_dir_deleted,
  diff_dir_opened,
  diff_dir_added,
  diff_dir_props_changed,
  diff_dir_closed    
};
      1. path is not a URL and start_revision != end_revision
      2. path is not a URL and start_revision == end_revision
      3. path is a URL and start_revision != end_revision
      4. path is a URL and start_revision == end_revision
      5. path is not a URL and no revisions given
   other.  When path is a URL there is no working copy. Thus
                depth,
                extra_ra_session, rev1, TRUE /* walk_deleted_dirs */,
                TRUE /* text_deltas */,
                pool));
           depth, ignore_ancestry, TRUE /* text_deltas */,
      svn_opt_revision_t *start_ignore;
      SVN_ERR(svn_client__repos_locations(&url1, &start_ignore, NULL, NULL,
                                          revision1, NULL,
          /* ### Ignores 'show_copies_as_adds'. */
/* Perform a summary diff between two working-copy paths.

   PATH1 and PATH2 are both working copy paths.  REVISION1 and
   REVISION2 are their respective revisions.

   All other options are the same as those passed to svn_client_diff5(). */
static svn_error_t *
diff_summarize_wc_wc(svn_client_diff_summarize_func_t summarize_func,
                     void *summarize_baton,
                     const char *path1,
                     const svn_opt_revision_t *revision1,
                     const char *path2,
                     const svn_opt_revision_t *revision2,
                     svn_depth_t depth,
                     svn_boolean_t ignore_ancestry,
                     const apr_array_header_t *changelists,
                     svn_client_ctx_t *ctx,
                     apr_pool_t *pool)
{
  svn_wc_diff_callbacks4_t *callbacks;
  void *callback_baton;
  const char *abspath1, *target1;
  svn_node_kind_t kind;

  SVN_ERR_ASSERT(! svn_path_is_url(path1));
  SVN_ERR_ASSERT(! svn_path_is_url(path2));

  /* Currently we support only the case where path1 and path2 are the
     same path. */
  if ((strcmp(path1, path2) != 0)
      || (! ((revision1->kind == svn_opt_revision_base)
             && (revision2->kind == svn_opt_revision_working))))
    return unsupported_diff_error
      (svn_error_create
       (SVN_ERR_INCORRECT_PARAMS, NULL,
        _("Only diffs between a path's text-base "
          "and its working files are supported at this time")));

  /* Find the node kind of PATH1 so that we know whether the diff drive will
     be anchored at PATH1 or its parent dir. */
  SVN_ERR(svn_dirent_get_absolute(&abspath1, path1, pool));
  SVN_ERR(svn_wc_read_kind(&kind, ctx->wc_ctx, abspath1, FALSE, pool));
  target1 = (kind == svn_node_dir) ? "" : svn_dirent_basename(path1, pool);
  SVN_ERR(svn_client__get_diff_summarize_callbacks(
            &callbacks, &callback_baton, target1,
            summarize_func, summarize_baton, pool));

  SVN_ERR(svn_wc_diff6(ctx->wc_ctx,
                       abspath1,
                       callbacks, callback_baton,
                       depth,
                       ignore_ancestry, FALSE /* show_copies_as_adds */,
                       FALSE /* use_git_diff_format */, changelists,
                       ctx->cancel_func, ctx->cancel_baton,
                       pool));
  return SVN_NO_ERROR;
}

  svn_wc_diff_callbacks4_t *callbacks;
  void *callback_baton;
  SVN_ERR(svn_client__get_diff_summarize_callbacks(
            &callbacks, &callback_baton,
            target1, summarize_func, summarize_baton, pool));

  SVN_ERR(svn_client__get_diff_editor(&diff_editor, &diff_edit_baton,
            depth,
            extra_ra_session, rev1, TRUE /* walk_deleted_dirs */,
            FALSE /* text_deltas */,
            callbacks, callback_baton,
            ctx->cancel_func, ctx->cancel_baton,
            NULL /* notify_func */, NULL /* notify_baton */, pool));
                  const apr_array_header_t *changelists,
  else if (! is_repos1 && ! is_repos2)
    return diff_summarize_wc_wc(summarize_func, summarize_baton,
                                path1, revision1, path2, revision2,
                                depth, ignore_ancestry,
                                changelists, ctx, pool);
   return unsupported_diff_error(
            svn_error_create(SVN_ERR_UNSUPPORTED_FEATURE, NULL,
                             _("Summarizing diff cannot compare repository "
                               "to WC")));
svn_client_diff6(const apr_array_header_t *options,
                 svn_stream_t *outstream,
                 svn_stream_t *errstream,
  diff_cmd_baton.outstream = outstream;
  diff_cmd_baton.errstream = errstream;
  diff_cmd_baton.no_diff_deleted = no_diff_deleted;
svn_client_diff_peg6(const apr_array_header_t *options,
                     svn_stream_t *outstream,
                     svn_stream_t *errstream,
  diff_cmd_baton.outstream = outstream;
  diff_cmd_baton.errstream = errstream;
  diff_cmd_baton.no_diff_deleted = no_diff_deleted;
                           depth, ignore_ancestry, changelists, pool);
                           peg_revision,
                           depth, ignore_ancestry, changelists, pool);