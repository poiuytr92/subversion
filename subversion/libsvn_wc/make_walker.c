/*
 * update.c :  routines for update and checkout
 *
 * ================================================================
 * Copyright (c) 2000 Collab.Net.  All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 
 * 3. The end-user documentation included with the redistribution, if
 * any, must include the following acknowlegement: "This product includes
 * software developed by Collab.Net (http://www.Collab.Net/)."
 * Alternately, this acknowlegement may appear in the software itself, if
 * and wherever such third-party acknowlegements normally appear.
 * 
 * 4. The hosted project names must not be used to endorse or promote
 * products derived from this software without prior written
 * permission. For written permission, please contact info@collab.net.
 * 
 * 5. Products derived from this software may not use the "Tigris" name
 * nor may "Tigris" appear in their names without prior written
 * permission of Collab.Net.
 * 
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL COLLAB.NET OR ITS CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ====================================================================
 * 
 * This software consists of voluntary contributions made by many
 * individuals on behalf of Collab.Net.
 */



#include <stdio.h>       /* for sprintf() */
#include <stdlib.h>
#include <apr_pools.h>
#include <apr_hash.h>
#include <apr_file_io.h>
#include <apr_strings.h>
#include "svn_types.h"
#include "svn_delta.h"
#include "svn_string.h"
#include "svn_error.h"
#include "svn_hash.h"



/* If PATH exists already, return an svn error containing ERR_TO_REPORT.
 *
 * If PATH doesn't exist, return 0.
 *
 * If unable to determine whether or not PATH exists, due to another
 * error condition, return an svn error containing that apr error.
 */
static svn_error_t *
check_existence (svn_string_t *path,
                 apr_status_t err_to_report,
                 apr_pool_t *pool)
{
  apr_status_t apr_err;
  apr_file_t *tmp_f;

  apr_err = apr_open (&tmp_f, path->data,
                     (APR_CREATE | APR_APPEND | APR_EXCL),
                     APR_OS_DEFAULT, pool);

  if (apr_err == APR_EEXIST)
    {
      svn_error_t *err 
        = svn_create_error (err_to_report, 0, path->data, NULL, pool);
      return err;
    }
  else if (apr_err)  /* some error other than APR_EEXIST */
    {
      svn_error_t *err 
        = svn_create_error (apr_err, 0, path->data, NULL, pool);
      return err;
    }
  else              /* path definitely does not exist */
    {
      apr_close (tmp_f);
      return 0;
    }
}


/* kff todo: this will want to be somewhere else, and get decided at
   configure time too probably.  For now let's just get checkout
   working. */
/* ben sez:  aha!  then this belongs in our "config.h" file! */

#define SVN_DIR_SEPARATOR '/'


static svn_error_t *
delete (svn_string_t *name, void *walk_baton, void *parent_baton)
{
}


static svn_error_t *
entry_pdelta (svn_string_t *name,
              void *walk_baton, void *parent_baton,
              svn_pdelta_t *entry_pdelta)
{
}


static svn_error_t *
add_directory (svn_string_t *name,
               void *walk_baton, void *parent_baton,
               svn_string_t *base_path,
               svn_version_t base_version,
               svn_pdelta_t *pdelta,
               void **child_baton)
{
}


static svn_error_t *
replace_directory (svn_string_t *name,
                   void *walk_baton, void *parent_baton,
                   svn_string_t *base_path,
                   svn_version_t base_version,
                   svn_pdelta_t *pdelta,
                   void **child_baton)
{
}


static svn_error_t *
finish_directory (void *child_baton)
{
}


static svn_error_t *
add_file (svn_string_t *name,
          void *walk_baton, void *parent_baton,
          svn_string_t *base_path,
          svn_version_t base_version,
          svn_pdelta_t *pdelta,
          svn_delta_handler_t **handler,
          void **handler_baton)
{
}


static svn_error_t *
replace_file (svn_string_t *name,
              void *walk_baton, void *parent_baton,
              svn_string_t *base_path,
              svn_version_t base_version,
              svn_pdelta_t *pdelta,
              svn_delta_handler_t *handler,
              void *handler_baton)
{
}



/* Apply a delta to a working copy, or to create a working copy.
 * 
 * If TARGET exists and is a working copy, or a subtree of a working
 * copy, then it is massaged into the updated state.
 *
 * If TARGET does not exist, a working copy is created there.
 *
 * If TARGET exists but is not a working copy, return error.
 *
 * todo: if TARGET == NULL, above rules apply with TARGET set to
 * the top directory mentioned in the delta?
 */
svn_error_t *
svn_wc_apply_delta (svn_delta_stream_t *src, 
                    svn_delta_read_fn_t *read_fn,
                    svn_string_t *target,
                    apr_pool_t *pool)
{
  char buf[BUFSIZ];
  apr_status_t err;
  svn_delta_walk_t walker;
  int len;

  /* Check existence of TARGET.  If present, just error out for now -- we
     can't do real updates, only fresh checkouts.  In the future, if
     TARGET exists we'll check if it's a working copy and only error
     out if it's not. */
  if (target)
    {
      svn_error_t *err;
      err = check_existence (target, SVN_ERR_OBSTRUCTED_UPDATE, pool);

      /* Whether or not err->apr_err == SVN_ERR_OBSTRUCTED_UPDATE, we
         want to return it to caller. */
      if (err)
        return err;
    }

  /* Else nothing in the way, so continue. */

  /* Set up the walker callbacks... */
  walker.delete            = delete;
  walker.entry_pdelta      = entry_pdelta;  /* kff todo */
  walker.add_directory     = add_directory;
  walker.replace_directory = replace_directory;
  walker.finish_directory  = finish_directory;
  walker.add_file          = add_file;
  walker.replace_file      = replace_file;

  /* ... and walk! */
  err = svn_delta_parse (read_fn, src, &walker, walk_baton, dir_baton, pool);

  return err;
}




/* 
 * local variables:
 * eval: (load-file "../svn-dev.el")
 * end:
 */
