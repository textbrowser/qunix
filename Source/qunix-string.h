/*
** Copyright (c) Alexis Megas.
** All rights reserved.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions
** are met:
** 1. Redistributions of source code must retain the above copyright
**    notice, this list of conditions and the following disclaimer.
** 2. Redistributions in binary form must reproduce the above copyright
**    notice, this list of conditions and the following disclaimer in the
**    documentation and/or other materials provided with the distribution.
** 3. The name of the author may not be used to endorse or promote products
**    derived from QUnix without specific prior written permission.
**
** QUNIX IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
** IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
** OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
** IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
** INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
** NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
** QUNIX, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef _qunix_string_h_
#define _qunix_string_h_

#include <QCoreApplication>

extern "C"
{
#include <string.h>
}

class qunix_string: public QObject
{
  Q_OBJECT

 public:
  qunix_string(QObject *parent):QObject(parent)
  {
  }

  ~qunix_string()
  {
  }

  QByteArray strerror_r(const int errnum)
  {
    QByteArray array(1024, '0');

#if (_POSIX_C_SOURCE >= 200112L) && ! _GNU_SOURCE
    if(::strerror_r(errnum, array.data(), array.length()) != 0)
      array.clear();
#else
    if(::strerror_r(errnum, array.data(), array.length()) == nullptr)
      array.clear();
#endif

    return array;
  }
};

#endif
