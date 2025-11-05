// SPDX-FileCopyrightText: 2025 Denis Danilov
// SPDX-License-Identifier: GPL-3.0-only

package org.codeberg.danilov.magnifier;

import android.os.Bundle;
import android.view.WindowManager;

import org.qtproject.qt.android.bindings.QtActivity;

public class MainActivity extends QtActivity {
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
    }
}
